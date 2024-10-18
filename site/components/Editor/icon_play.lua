local luax = require('site/lib/luax');

function icon_play(scale)
    local scale = 1 / scale;
    return luax('svg', {width=100/scale, height=100/scale }, {
        luax('circle', { cx=50/scale, cy=50/scale, r=45/scale, fill="#AA36EF"}),
        luax('polygon', { points=luax('', {
            40/scale, ',', 30/scale, ' ',
            70/scale, ',', 50/scale, ' ',
            40/scale, ',', 70/scale, ' ',
        }), fill="white"}),
    })
end

return icon_play;