def rand(max = 1)
  throw "fuck"
end

def Kernel.rand(max = 1)
  throw "fuck"
end

def srand(max = 1)
  throw "shit"
end

def Kernel.srand(max = 1)
  throw "shit"
end

class Random
  def rand(a = 1)
    throw "fuck"
  end

  def self.rand(a = 1)
    throw "fuck"
  end

  def srand(a = 1)
    throw "shit"
  end

  def self.srand(a = 1)
    throw "shit"
  end
end

class Array
  def self.shuffle(a = [])
    throw "sucks"
  end

  def shuffle(a = [])
    throw "sucks"
  end

  def sample(a = [])
    throw "sucks"
  end

  def self.sample(a = [])
    throw "sucks"
  end
end
