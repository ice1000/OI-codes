module ListOps where
import Prelude hiding (head, tail, init, last)

head (a : _) = a
last = head . reverse
tail (_ : a) = a
init = reverse . tail . reverse
