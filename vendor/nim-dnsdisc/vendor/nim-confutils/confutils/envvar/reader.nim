import
  tables, typetraits, options, os,
  serialization/[object_serialization, errors],
  ./utils

type
  EnvvarReader* = object
    prefix: string
    key: seq[string]

  EnvvarError* = object of SerializationError

  EnvvarReaderError* = object of EnvvarError

  GenericEnvvarReaderError* = object of EnvvarReaderError
    deserializedField*: string
    innerException*: ref CatchableError

proc handleReadException*(r: EnvvarReader,
                          Record: type,
                          fieldName: string,
                          field: auto,
                          err: ref CatchableError) =
  var ex = new GenericEnvvarReaderError
  ex.deserializedField = fieldName
  ex.innerException = err
  raise ex

proc init*(T: type EnvvarReader, prefix: string): T =
  result.prefix = prefix

proc readValue*[T](r: var EnvvarReader, value: var T) =
  mixin readValue
  # TODO: reduce allocation

  when T is string:
    let key = constructKey(r.prefix, r.key)
    value = os.getEnv(key)

  elif T is (SomePrimitives or range):
    let key = constructKey(r.prefix, r.key)
    getValue(key, value)

  elif T is Option:
    template getUnderlyingType[T](_: Option[T]): untyped = T
    let key = constructKey(r.prefix, r.key)
    if existsEnv(key):
      type uType = getUnderlyingType(value)
      when uType is string:
        value = some(os.getEnv(key))
      else:
        value = some(r.readValue(uType))

  elif T is (seq or array):
    when uTypeIsPrimitives(T):
      let key = constructKey(r.prefix, r.key)
      getValue(key, value)

    else:
      let key = r.key[^1]
      for i in 0..<value.len:
        r.key[^1] = key & $i
        r.readValue(value[i])

  elif T is (object or tuple):
    type T = type(value)
    when T.totalSerializedFields > 0:
      let fields = T.fieldReadersTable(EnvvarReader)
      var expectedFieldPos = 0
      r.key.add ""
      value.enumInstanceSerializedFields(fieldName, field):
        when T is tuple:
          r.key[^1] = $expectedFieldPos
          var reader = fields[][expectedFieldPos].reader
          expectedFieldPos += 1
        else:
          r.key[^1] = fieldName
          var reader = findFieldReader(fields[], fieldName, expectedFieldPos)

        if reader != nil:
          reader(value, r)
      discard r.key.pop()

  else:
    const typeName = typetraits.name(T)
    {.fatal: "Failed to convert from Envvar an unsupported type: " & typeName.}
