local luax = require('site/lib/luax');
local Config = require('site/config');

function LU5Canvas(props)

    return luax('div', {
        luax('canvas', { id=props.id..'_canvas', style="display:none;" }),
        luax('div', {class="flex-col", style="margin: 1.5rem 0;"}, {
            luax('div', { id=props.id..'_console', style="min-width: 22rem; max-height: 16rem;"}, {
                luax('p', {class="text white monospace underline", style="margin: 0.2rem 0 0.6rem 0;"}, 'Output')
            }),
        }),
        luax('script', {type="module"}, {
            'import Console from "',  Config.cdn.lu5_console, '";',
            'import * as lu5 from "', Config.cdn.lu5_wasm_lib,    '";',
            'const ',props.id..'_console',' = new Console(`',props.id..'_console','`);',
            'lu5.init("', Config.cdn.lu5_wasm ,'")',
                '.then(vm => vm.setCanvas("',props.id..'_canvas','"))',
                '.then(vm => vm.attach(1, ',props.id..'_console','))',
                '.then(vm => vm.attach(2, ',props.id..'_console','))',
                '.then(vm => vm.attach(2, console))',
                '.then(vm => vm.execute(`', props.source ,'`));',
                '\n'
        })
    })
end

return LU5Canvas;