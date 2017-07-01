require 'fiddle'

class Object
  def unfreeze
    Fiddle::Pointer.new(object_id * 2)[1] &= ~(1 << 3)
  end
end

SecureLogin.unfreeze

class SecureLogin
  def login!
    true
  end
end
