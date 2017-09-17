import java.util
import java.util.function
import java.util.function.{Consumer, Predicate}

class DFA {
  var name = 0
  var nodes = new Array[DFA](2)
  var expr = new java.util.ArrayList[String]

  def verify: Boolean = java.util.Arrays.stream(nodes).noneMatch(new Predicate[DFA] {
    override def test(t: DFA): Boolean = t != null
  })

  def simulateRun(str: String, target: DFA): Boolean = {
    if (str.length == 1) {
      if (nodes(str.charAt(0) - '0') == null) {
        nodes(str.charAt(0) - '0') = target
        return true
      }
      assert(nodes(str.charAt(0) - '0') eq target)
      return false
    }
    nodes(str.charAt(0) - '0').simulateRun(str.substring(1), target)
  }

  def independent: Boolean = expr.size == 1 && expr.get(0).matches("^[^a-z]*$")

  def initialize(): Unit = {
    expr.add("0" + ('a' + nodes(0).name).toChar)
    expr.add("1" + ('a' + nodes(1).name).toChar)
    if (name == 0) expr.add("")
  }

  def applyArdensLemma(): Unit = {
    var found = -1
    var prefix = ""
    var i = 0
    var flag = true
    while (i < expr.size && flag) {
      if (expr.get(i).endsWith(String.valueOf(('a' + name).toChar))) {
        found = i
        prefix = expr.get(i).substring(0, expr.get(i).length - 1)
        flag = false
      }
      i += 1
    }
    if (found == -1) return
    val exprNew = new java.util.ArrayList[String]
    i = 0
    while (i < expr.size) {
      if (i != found) exprNew.add("(" + prefix + ")*" + expr.get(i))
      i += 1
    }
    expr = exprNew
  }

  def substitute(`with`: DFA): Unit = {
    val exprNew = new java.util.ArrayList[String]
    import scala.collection.JavaConversions._
    for (exp <- expr) {
      if (exp.endsWith(String.valueOf(('a' + `with`.name).toChar))) {
        val prefix = exp.substring(0, exp.length - 1)
        import scala.collection.JavaConversions._
        for (ex <- `with`.expr) {
          exprNew.add(prefix + ex)
        }
      }
      else exprNew.add(exp)
    }
    expr = exprNew
  }

  def merge(): Unit = {
    val merger = new java.util.HashMap[Character, java.util.List[String]]
    expr.forEach(new Consumer[String] {
      override def accept(exp: String): Unit = {
        merger.computeIfAbsent(exp.charAt(exp.length - 1), new function.Function[Character, java.util.List[String]] {
          override def apply(t: Character) = new java.util.ArrayList[String]()
        }).add(exp.substring(0, exp.length - 1))
      }
    })
    val exprNew = new java.util.ArrayList[String]
    import scala.collection.JavaConversions._
    for (entry <- merger.entrySet) {
      if (entry.getValue.size == 1) exprNew.add(entry.getValue.get(0) + entry.getKey)
      else exprNew.add("(" + String.join("|", entry.getValue) + ")" + entry.getKey)
    }
    expr = exprNew
  }
}

class Solution {
  def regexDivisibleBy(n: Int): String = {
    assert(n <= 'z' - 'a')
    // Special case for n = 1 (ALL numbers...)
    if (n == 1) return "(0|1)*"
    val net = new Array[DFA](n)
    var i = 0
    while (i < n) {
      net(i) = new DFA
      net(i).name = i.toChar
      i += 1
    }
    var cont = true
    i = 0
    while (cont) {
      cont = net(0).simulateRun(Integer.toString(i, 2), net(i % n))
      i += 1
    }
    java.util.Arrays.stream(net).forEach(new Consumer[DFA] {
      override def accept(t: DFA): Unit = t.initialize()
    })
    var subName = n - 1
    while (subName >= 0) {
      val which = net(subName)
      subName -= 1
      java.util.Arrays.stream(net).forEach(new Consumer[DFA] {
        override def accept(t: DFA): Unit = t.applyArdensLemma()
      })
      java.util.Arrays.stream(net).forEach(new Consumer[DFA] {
        override def accept(t: DFA): Unit = {
          t.substitute(which)
        }
      })
      java.util.Arrays.stream(net).forEach(new Consumer[DFA] {
        override def accept(t: DFA): Unit = t.merge()
      })
    }
    net(0).expr.get(0)
  }
}