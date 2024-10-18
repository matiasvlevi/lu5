local LU5Canvas = require('site/components/LU5Canvas');



function MethodExample(method, example, index)
    return example.source ~= nil and luax('div', {class="method-example flex items-center"}, {
        luax('pre', {class="example-code noselect"},{
            luax('code', {class="language-lua noselect"}, { example.source })
        }),
        example.live and LU5Canvas({
            id=(method.name .. '_' .. index),
            source=example.source
        }) or ''
    }) or ''
end

return MethodExample;