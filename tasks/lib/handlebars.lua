function use_template(template, content, metadata)

    local page = template;

    if (metadata == nil) then 
        metadata = {}
    end

    -- inject metadata if any
    for k,v in pairs(metadata) do 
        content[k] = v 
    end

    -- Replace all specified template fields
    for k,v in pairs(content) do
        page = string.gsub(page, '{{'.. k ..'}}', v);
    end

    -- Remove unused template fields
    while (string.find(page, '{{.-}}')) do
        page = string.gsub(page, '{{.-}}', '');
    end

    return page;
end

return {
	use_template=use_template
}