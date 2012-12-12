float4 vedoColor = (1,1,1,1);
IN(float4,color);
IN(uint4,index);

color = vedoColor*dot(color,index);

return color;