def first_non_consecutive(arr)
  return nil if arr.size() <= 1
  return arr[1] if arr[0] + 1 != arr[1]
  return first_non_consecutive(arr.drop 1)
end
