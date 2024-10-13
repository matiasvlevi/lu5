local luax = require('site/lib/luax');

function LU5Canvas(props)
    return luax('div', {
        luax('canvas', { id=props.id..'_canvas', style="display:none;" }),
        luax('div', {class="flex-col", style="margin: 1.5rem 0;"}, {
            luax('div', { id=props.id..'_console', style="min-width: 22rem; max-height: 16rem;"}, {
                luax('p', {class="text white monospace underline", style="margin: 0.2rem 0 0.6rem 0;"}, 'Output')
            }),
        }),
        luax('script', {
            'const ',props.id..'_console',' = new lu5.Console(`',props.id..'_console','`);',
            'lu5.init()',
                '.then(vm => vm.setCanvas("',props.id..'_canvas','"))',
                '.then(vm => vm.attach(1, ',props.id..'_console','))',
                '.then(vm => vm.attach(2, ',props.id..'_console','))',
                '.then(vm => vm.attach(2, console))',
                '.then(vm => vm.execute(`', props.source ,'`));',
                '\n'
        }),
        luax('')
    })
end

return LU5Canvas;