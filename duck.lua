
local duckCnt = 0
local roundCnt = 8

local bottomBoard = 700

local lastX = 0
local lastY = 0

duckPic = 'duck.png'

function CheckRound()
    if roundCnt <= 0 then
        print('reload')
    end
end

function CheckBorders(x, y)
    corridor = 20
    if y > bottomBoard then
        return false
    end
    if (mod(x - lastX) < corridor) and y > lastY then
        return false
    end
    return true
end

function ShootLoop()

    while duckCnt < 10 do
        x, y, findD = FindDuck(duckPic)
        if findD and CheckBorders(x, y) then
            print('shoot')
            --print('shoot' .. x .. y)
            duckCnt = duckCnt + 1
            CheckRound()
        end
    end
    print('all birds down')
end

