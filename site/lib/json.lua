local luax = require('site/lib/luax');

function json_matcher(key, value)
    local key_str = (type(key) ~= "string") and '' or '"' .. key .. '":';
    return {
        string=function(t) 
            local esc_value = value
                :gsub("\n", "\\n")
                :gsub("\r", "\\r")
                :gsub("\t", "\\t")
                :gsub("\"", "\\\"");
            
            return key_str .. '"' .. esc_value .. '"';
        end,
        number=function(t)
            return key_str .. tostring(value);
        end,
        integer=function(t)
            return key_str .. tostring(value);
        end,
        table=function(t)
            local is_numeric = (value[1] ~= nil);
            if is_numeric then
                local values_str = {};
                for i, value_in_arr in ipairs(value) do
                    table.insert(values_str, luax.match(type(value_in_arr), json_matcher(i, value_in_arr)));
                end

                return key_str .. '[' .. luax.join(values_str, ',') .. ']';
            else
                local raw = {}

                for key, v in pairs(value) do
                    table.insert(raw, luax.match(type(v), json_matcher(key, v)))
                end

                return key_str .. "{" .. luax.join(raw, ',') .. "}";
            end
        end,
        default=''
    };
end

return {
    stringify=function(obj) 
        return luax.match(type(obj), json_matcher(nil, obj))
    end
};