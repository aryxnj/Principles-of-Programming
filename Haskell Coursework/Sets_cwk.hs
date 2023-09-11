module Coursework where

{-
  Your task is to design a datatype that represents the mathematical concept of a (finite) set of elements (of the same type).
  We have provided you with an interface (do not change this!) but you will need to design the datatype and also 
  support the required functions over sets.
  Any functions you write should maintain the following invariant: no duplication of set elements.

  There are lots of different ways to implement a set. The easiest is to use a list
  (as in the example below). Alternatively, one could use an algebraic data type, or 
  wrap a binary search tree.
  Extra marks will be awarded for efficient implementations if appropriate.

  You are NOT allowed to import anything from the standard library or other libraries.
  Your edit of this file should be completely self-contained.

  DO NOT change the type signatures of the functions below: if you do,
  we will not be able to test them and you will get 0% for that part. While sets are unordered collections,
  we have included the Ord constraint on most signatures: this is to make testing easier.

  You may write as many auxiliary functions as you need. Please include everything in this file.
-}

{-
   PART 1.
   You need to define a Set datatype. Below is an example which uses lists internally.
   It is here as a guide, but also to stop ghci complaining when you load the file.
   Free free to change it.
-}

-- you may change this to your own data type
newtype Set a = Set { unSet :: [a] }
   deriving (Show)

{-
   PART 2.
   If you do nothing else, at least get the following two functions working. They
   are required for testing purposes.
-}

-- toList {2,1,4,3} => [1,2,3,4]
-- the output must be sorted.
toList :: (Ord a) => Set a -> [a]
toList (Set inputSet) = sort inputSet

sort :: (Ord a) => [a] -> [a]
sort [] = []
sort (x:xs) = insert x (sort xs)
    where insert x [] = [x]
          insert x (y:ys)
              | x <= y    = x : y : ys
              | otherwise = y : insert x ys


-- fromList [2,1,1,4,5] => {2,1,4,5}
fromList :: Ord a => [a] -> Set a
fromList = Set . fromListHelper []

fromListHelper :: Ord a => [a] -> [a] -> [a]
fromListHelper acc [] = reverse acc
fromListHelper acc (x:xs) = if x `elem` acc then fromListHelper acc xs else fromListHelper (x:acc) xs


{-
   PART 3.
   Your Set should contain the following functions.
   DO NOT CHANGE THE TYPE SIGNATURES.
-}

-- test if two sets have the same elements.
instance (Ord a) => Eq (Set a) where
  s1 == s2 = (sort $ toList s1) == (sort $ toList s2)

-- the empty set
empty :: Set a
empty = Set []

-- Set with one element
singleton :: a -> Set a
singleton x = Set [x]


-- insert an element of type a into a Set
-- make sure there are no duplicates!
insert :: (Ord a) => a -> Set a -> Set a
insert x (Set xs) = Set (insert x xs)
  where
    insert :: (Ord a) => a -> [a] -> [a]
    insert x [] = [x]
    insert x (y:ys)
        | x < y = x:y:ys
        | x == y = y:ys
        | otherwise = y:(insert x ys)


-- join two Sets together
-- be careful not to introduce duplicates.
union :: (Ord a) => Set a -> Set a -> Set a
union (Set xs) (Set ys) = Set (sort (removeDups (xs ++ ys)))

removeDups :: Ord a => [a] -> [a]
removeDups [] = []
removeDups (x:xs) 
    | x `elem` xs = removeDups xs 
    | otherwise = x : removeDups xs


-- return the common elements between two Sets
intersection :: (Ord a) => Set a -> Set a -> Set a
intersection (Set xs) (Set ys) = Set (removeDups (sort (filter (`elem` ys) xs)))


-- all the elements in Set A *not* in Set B,
-- {1,2,3,4} `difference` {3,4} => {1,2}
-- {} `difference` {0} => {}
difference :: (Ord a) => Set a -> Set a -> Set a
difference (Set xs) (Set ys) = Set (removeDups (sort (filter (`notElem` ys) xs)))


-- is element *a* in the Set?
member :: (Ord a) => a -> Set a -> Bool
member x (Set xs) = x `elem` (removeDups xs)


-- how many elements are there in the Set?
cardinality :: Set a -> Int
cardinality (Set xs) = length (xs)


setmap :: (Ord b) => (a -> b) -> Set a -> Set b
setmap f (Set xs) = Set (removeDups (map f xs))


setfoldr :: (a -> b -> b) -> Set a -> b -> b
setfoldr f (Set xs) acc = foldr f acc xs


-- powerset of a set
-- powerset {1,2} => { {}, {1}, {2}, {1,2} }
powerSet :: Set a -> Set (Set a)
powerSet (Set xs) = Set (powerSetHelper [] xs)

powerSetHelper :: [a] -> [a] -> [Set a]
powerSetHelper acc [] = [Set acc]
powerSetHelper acc (x:xs) = (powerSetHelper acc xs) ++ (powerSetHelper (x:acc) xs)


-- cartesian product of two sets
cartesian :: Set a -> Set b -> Set (a, b)
cartesian (Set xs) (Set ys) = Set [(x, y) | x <- xs, y <- ys]


-- partition the set into two sets, with
-- all elements that satisfy the predicate on the left,
-- and the rest on the right
partition :: (a -> Bool) -> Set a -> (Set a, Set a)
partition p (Set xs) = partition' xs ([],[])
  where partition' [] (left,right) = (Set left, Set right)
        partition' (x:xs) (left,right)
            | p x       = partition' xs (x:left, right)
            | otherwise = partition' xs (left, x:right)


{-
   On Marking:
   Be careful! This coursework will be marked using QuickCheck, against Haskell's own
   Data.Set implementation. Each function will be tested for multiple properties.
   Even one failing test means 0 marks for that function.

   Marks will be lost for too much similarity to the Data.Set implementation.

   Pass: creating the Set type and implementing toList and fromList is enough for a
   passing mark of 40%.

-}
