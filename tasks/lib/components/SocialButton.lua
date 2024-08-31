

function SocialButton(props)
    return luax('a', {href=props.link, class="flex items-center",style="gap: 0.5rem; color: " .. props.color .. ";"}, {
        luax('img', {src=props.icon}),
        luax('span', {class="small dark underline"}, props.label or '')
    });
end

return  SocialButton