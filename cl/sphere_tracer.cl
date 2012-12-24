
typedef struct usr_Camera
{
	float4 p;
	float4 w;
	float4 u;
	float4 v;
	float2 fov;
	float2 dim;
} Camera;
typedef struct usr_Ray
{
	float4 p;
	float4 d;
}Ray;
float2 computeRay(Camera * cam,float2 coords,Ray * outRay)
{
	float a = tan(cam->fov.x/2.0)*((coords.x - cam->dim.x/2.0)/(cam->dim.x/2.0));
	
	float b = tan(cam->fov.y/2.0)*((cam->dim.y/2.0 - coords.y)/(cam->dim.y/2.0));
	
	outRay->p = cam->p;
	outRay->d = a*cam->u+b*cam->v - cam->w;
	outRay->d = normalize(outRay->d);
	float2 ret;
	ret.x = a;ret.y=b;
	return ret;
	
	
}

bool rayTrinagelIntersect(const Ray * ray,float4 vert0,float4 vert1,float4 vert2,float * u,float * v,float * t)
{
	float4 edge1,edge2,tvec,pvec,qvec;
	float det,inv_det;
	
	edge1 = vert1-vert0;
	edge2 = vert2-vert0;
	
	pvec = cross(ray->d,edge2);
	
	det = dot(edge1,pvec);
	if(det < 0.00001)
		return false;
	
	tvec = ray->p - vert0;
	
	*u = dot(tvec,pvec);
	
	if(*u < 0.0 || *u > det)
		return false;
		
	qvec = cross(tvec,edge1);
	
	*v = dot(ray->d,qvec);
	
	if(*v < 0.0 || *u+*v > det)
		return false;
	
	*t = dot(edge2,qvec);
	inv_det = 1.0/det;
	*t *= inv_det;
	*u *= inv_det;
	*v *= inv_det;
	return true;
	
	
}
void initCamera(__constant float4 * camera,Camera * cam)
{
	cam->p = camera[0];
	cam->w = camera[1];
	cam->u = camera[3];
	cam->v = camera[4];
	
	cam->fov = camera[2].zw;
	cam->dim =  camera[2].xy;
}
bool raySphereIntersect(uint offset,__constant void *renderIndex,const Ray * ray,float * distan)
{
	float r = *((__constant float*)(renderIndex+offset));
	
	float4 center = *((__constant float4*)(renderIndex+offset + sizeof(float)));
	
	float4 rp = ray->p-center;
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
	
	return true;
	
}
#define SIZE_ONE_INDEX_OBJ sizeof(uint)+sizeof(uint)*3
float4 traceRay(const Ray * ray,__constant void * Materials,__constant void *renderIndex,__constant void *RenderData)
{
  uint objectNum = *((__constant uint*)renderIndex);
  float distan = 999999.9;
  uint materialOffset;
  uint scriptId;
  bool intersected = false;
  
  for(uint i =0;i<objectNum;i++)
  {
    float d;
    uint sc = *((__constant uint*)(renderIndex+sizeof(uint)+i*(SIZE_ONE_INDEX_OBJ)));
    uint objectOffset = *((__constant uint*)(renderIndex+sizeof(uint)+sizeof(uint)+i*(SIZE_ONE_INDEX_OBJ)));
   
   // raySphereIntersect(objectOffset,RenderData,ray,&d);
    if(raySphereIntersect(objectOffset,RenderData,ray,&d) && d < distan)
    {
      intersected = true;
      d = distan;
      scriptId = *((__constant uint*)(renderIndex+sizeof(uint)+i*(SIZE_ONE_INDEX_OBJ)+sizeof(uint)
			+sizeof(uint)));
      materialOffset = *((__constant uint*)(renderIndex+sizeof(uint)+i*(SIZE_ONE_INDEX_OBJ)+sizeof(uint)
			+sizeof(uint)+sizeof(uint)));
      
    }
  }
  if(intersected)
  {
    return applyScript(scriptId,Materials+materialOffset);
  }
  return (float4)(0,0,0,1);
}
__kernel void renderKernel(__write_only image2d_t output,//0
			   __constant float4 *camera,    //1
			   __constant void *materials,   //2
			   __constant void *renderIndex, //3
			   __constant void *renderData)  //4
{
	int i = get_global_id(0);
	Camera cam;
	initCamera(camera,&cam);
	
	// Strating to create rayes from view port
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
	float4 color = (float4)(0.0,0.0,0.0,1.0);//*(dot(ray.d,cam.w)/2.0+0.5)
	float intense;
	float u,v,t;
	
	
	
	/*if(rayTrinagelIntersect(&ray,(float4)(0.0,1.0,-8,1),(float4)(-0.5,0,-8,1),(float4)(0.5,0,-8,1),&u,&v,&t)
	||rayTrinagelIntersect(&ray,(float4)(0.0,1.0,-8,1),(float4)(0.5,0,-8,1),(float4)(-0.5,0,-8,1),&u,&v,&t))
	//||rayTrinagelIntersect(&ray,(float4)(0.0,1.0,8,1),(float4)(-0.5,0,8,1),(float4)(0.5,0,8,1),&u,&v,&t)
	//||rayTrinagelIntersect(&ray,(float4)(0.0,1.0,8,1),(float4)(0.5,0,8,1),(float4)(-0.5,0,8,1),&u,&v,&t))//raySphereIntersect(spherePos[0],sphereColor[0].x,&ray,&di,&intense)
	{
		//color = applyMaterial(0,materials);
		//if(c.x > 255)c.x = 255;
		//color.x = ((__global uint4*)materials)[0].x;
		color.x = 255;
		//color = (uint4)(sphereColor[0].y*255,sphereColor[0].z*255,sphereColor[0].w*255,255);//applyMaterial(0,materials);//
		//color.xyz *= intense;
		
	}*/
	color = traceRay(&ray,materials,renderIndex,renderData);
	write_imagef(output,coord,color);
	
}
