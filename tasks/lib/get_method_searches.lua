
function get_method_searches(arr)
    local methods = {}
    for _, mod in ipairs(arr) do
        for _, method in ipairs(mod.methods) do
            table.insert(methods, {
                name = method.doc.name,
                module = mod.source
                -- -- Not needed
                --   description = method.doc.description,
                --   type = method.doc._type
            })
        end
    end
    return methods
end

return get_method_searches