module Graph where
1;4601;0c
import Control.Applicative

type Node = Char
type Arc  = (Node, Node)

solveGraph :: Node -> Node -> [Arc] -> Bool
solveGraph s = f [s] s
  where f v s e arcs = elem (s, e) arcs
          || s == e
          || any id ((\t -> f (t : v) t e arcs) <$>
                  [ y | (x, y) <- arcs, x == s, not $ elem y v ])
--

