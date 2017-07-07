require 'ipaddr'

class String
  def ipv4_address?
    !(IPAddr.new(self) rescue nil).nil?
  end
end
