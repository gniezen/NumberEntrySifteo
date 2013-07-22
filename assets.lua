IconAssets = group{quality=9.95}
Icon = image{"icon.png"}


GameAssets = group{}

function frames(fmt, count)
    t = {}
    for i = 0, count-1 do
        t[1+#t] = string.format(fmt, i)
    end
    return t
end

Numbers = image{ frames("images/numbers%d.png", 60),pinned=true}



