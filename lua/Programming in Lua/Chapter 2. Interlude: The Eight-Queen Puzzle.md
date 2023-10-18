```lua
N = 8

-- check whether position (n, c) is free from attacks
function isplaceok(a, n, c)
  for i = 1, n - 1 do -- for each queen already placed
    if (a[i] == c) or
        --[[
            a[i]: col index
            i: row index
            a[i] - i = col_index - row_index
            c: col index
            n: row index
            c - n = col_index - row_indexjk
            ]]
        (a[i] - i == c - n) or 
        (a[i] + i == c + n) then
      return false
    end
  end
  return true
end

-- print a board
function printsolution(a)
  for i = 1, N do
    for j = 1, N do
      -- write "X" or "-" plus a space
      io.write(a[i] == j and "X" or "-", " ")
    end
    io.write("\n")
  end
  io.write("\n")
end

-- add to board 'a' all queens from 'n' to 'N'
function addqueen(a, n)
  if n > N then -- all queens have been placed?
    printsolution(a)
  else          -- try to place n-th quenen
    for c = 1, N do
      if isplaceok(a, n, c) then
        a[n] = c
        addqueen(a, n + 1)
      end
    end
  end
end

-- run the program
addqueen({}, 1)
```

