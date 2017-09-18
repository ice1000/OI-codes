import java.io.ByteArrayOutputStream

object Base91 {

  private var ENCODING_TABLE: Array[Byte] = null
  private var DECODING_TABLE: Array[Byte] = null
  private var BASE = 0
  private val AVERAGE_ENCODING_RATIO = 1.2297f

  val ts = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\""
  ENCODING_TABLE = ts.getBytes
  BASE = ENCODING_TABLE.length
  DECODING_TABLE = new Array[Byte](256)
  var i = 0
  while (i < 256) {
    DECODING_TABLE(i) = -1
    i += 1
  }
  i = 0
  while (i < BASE) {
    DECODING_TABLE(ENCODING_TABLE(i)) = i.toByte
    i += 1
  }

  def encode(data: String): String = new String(encode(data.getBytes))

  def encode(data: Array[Byte]): Array[Byte] = {
    val estimatedSize = Math.ceil(data.length * AVERAGE_ENCODING_RATIO).toInt
    val output = new ByteArrayOutputStream(estimatedSize)
    var ebq = 0
    var en = 0
    for (aData <- data) {
      ebq |= (aData & 255) << en
      en += 8
      if (en > 13) {
        var ev = ebq & 8191
        if (ev > 88) {
          ebq >>= 13
          en -= 13
        }
        else {
          ev = ebq & 16383
          ebq >>= 14
          en -= 14
        }
        output.write(ENCODING_TABLE(ev % BASE))
        output.write(ENCODING_TABLE(ev / BASE))
      }
    }
    if (en > 0) {
      output.write(ENCODING_TABLE(ebq % BASE))
      if (en > 7 || ebq > 90) output.write(ENCODING_TABLE(ebq / BASE))
    }
    output.toByteArray
  }

  def decode(data: String): String = new java.lang.String(decode(data.getBytes))

  def decode(data: Array[Byte]): Array[Byte] = {
    if (data.length == 0) return new Array[Byte](0)
    var dbq = 0
    var dn = 0
    var dv = -1
    val estimatedSize = data.length / AVERAGE_ENCODING_RATIO.round
    val output = new ByteArrayOutputStream(estimatedSize)
    var i = 0
    while (i < data.length) {
      if (DECODING_TABLE(data(i)) != -1) {
        if (dv == -1) dv = DECODING_TABLE(data(i))
        else {
          dv += DECODING_TABLE(data(i)) * BASE
          dbq |= dv << dn
          if ((dv & 8191) > 88) dn += 13 else dn += 14
          do {
            output.write(dbq.toByte)
            dbq >>= 8
            dn -= 8
          } while (dn > 7)
          dv = -1
        }
        i += 1
      }
    }
    if (dv != -1) output.write((dbq | dv << dn).toByte)
    output.toByteArray
  }

}