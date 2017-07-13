# not written by me myself
# see https://github.com/esphas/esphas.github.io/blob/master/_posts/2017-06-16-recent_days.md

def boolfuck code, input = ''
  reader = pointer = pt = 0
  tapes = [[], []]
  tape = tapes[0]
  stack = []
  input = input.unpack('b*')[0].chars().map(&:to_i).reverse()
  output = []

  while reader < code.size
    case code[reader]
    when '+'
      tape[pt] = (tape[pt] || 0) ^ 1
    when ','
      tape[pt] = input.pop || 0
    when ';'
      output.push(tape[pt] || 0)
    when '<'
      pointer -= 1
      tape = pointer < 0 ? tapes[1] : tapes[0]
      pt = pointer < 0 ? -pointer-1 : pointer
    when '>'
      pointer += 1
      tape = pointer < 0 ? tapes[1] : tapes[0]
      pt = pointer < 0 ? -pointer-1 : pointer
    when '['
      if (tape[pt] || 0) == 0
        match = /^(?<b>\[(?:\g<b>|[^\[\]])*?\])/.match(code[reader, code.size])
        break if match == nil
        reader += match[0].size - 1
      else
        stack.push reader
      end
    when ']'
      if (tape[pt] || 0) == 0
        stack.pop
      else
        reader = stack.last
      end
    end
    reader += 1
  end
  [output.map(&:to_s).join('')].pack 'b*'
end
