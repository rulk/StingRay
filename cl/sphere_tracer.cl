typedef struct usr_Camera
{
	float4 p;
	float3 w;
	float3 u;
	float3 v;
	float2 fov;
	float2 dim;
} Camera;
typedef struct usr_Ray
{
	float4 p;
	float3 d;
}Ray;
float2 computeRay(Camera * cam,float2 coords,Ray * outRay)
{
	float a = tan(cam->fov.x/2.0)*((coords.x - cam->dim.x/2.0)/(cam->dim.x/2.0));
	
	float b = tan(cam->fov.y/2.0)*((cam->dim.y/2.0 - coords.y)/(cam->dim.y/2.0));
	
	outRay->p = cam->p;
	outRay->d = a*cam->u+b*cam->v + cam->w;
	outRay->d = normalize(outRay->d);
	float2 ret;
	ret.x = a;ret.y=b;
	return ret;
	
	
}
bool raySphereIntersect(float4 center,float r,const Ray * ray,float * distan,float * intense)
{
	float3 rp = (ray->p-center).xyz;
	float b = 2*dot(ray->d,rp);
	float a = dot(ray->d,ray->d);
	float c = dot(rp,rp);
	c -= r*r;
	
	float discrim = b*b - 4*a*c;
	if(discrim < 0)
		return false;
	float d1 = (-b + sqrt(discrim))/(2*a);
	float d2 = (-b - sqrt(discrim))/(2*a);
	if(d1 > d2)
		*distan = d2;
	else 
		*distan = d1;
	*intense = 1.0;
	if(discrim <0.1 && discrim > -0.1)
		*intense = 0.5;
	return true;
	
}
__kernel void main(__write_only image2d_t output,__global float4 *camera, __global float4 *spherePos, __global float4 *sphereColor)
{
	int i = get_global_id(0);
	Camera cam;
	cam.p = camera[0];
	cam.w = camera[1].xyz;
	cam.u = camera[3].xyz;
	cam.v = camera[4].xyz;
	cam.fov = camera[2].zw;
	cam.dim =  camera[2].xy;
	int dy = (float)cam.dim.y;
	int2 coord;
	coord.x = i/cam.dim.x;
	coord.y  = i - (i/dy)*dy;
	float2 coordf;
	coordf.x = (float) coord.x + 0.5;
	coordf.y = (float) coord.y + 0.5;
	Ray ray;
	float2 c = computeRay(&cam,coordf,&ray);
	float di ;//= dot(ray.d,cam.w)/2.0 +0.5;
	uint4 color = (uint4)(0,0,0,255);//*(dot(ray.d,cam.w)/2.0+0.5)
	float intense;
	if(raySphereIntersect(spherePos[0],sphereColor[0].x,&ray,&di,&intense))
	{
		
		color.xyz = (uint3)(sphereColor[0].y*255,sphereColor[0].z*255,sphereColor[0].w*255);
		color.xyz *= intense;
		
	}
	write_imageui(output,coord,color);
	
}
