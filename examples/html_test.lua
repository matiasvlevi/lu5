local luax = require('site/lib/luax');



local text = luax('div', {class="container"}, {
    luax('button', 'CLICK ME')
})

print(text);