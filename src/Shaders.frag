uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec3 u_pos;


const float MAX_DIST = 99999.0;
vec3 light = normalize(vec3(-0.5, 0.75, -1.0));
mat2 rot(float a)
{
	float s = sin(a);
	float c = cos(a);
	return mat2(c, -s, s, c);
}
vec3 getSky(vec3 rd)
{
	vec3 col = vec3(0.3, 0.6, 1.0);
	vec3 sun = vec3 (0.95, 0.9, 1.0);
	sun *= max(0.0, pow(dot(rd,light), 128.0));
	return clamp(sun + col, 0.1, 1.0);
}

vec3 triIntersect( in vec3 ro, in vec3 rd, in vec3 v0, in vec3 v1, in vec3 v2 )
{
    vec3 v1v0 = v1 - v0;
    vec3 v2v0 = v2 - v0;
    vec3 rov0 = ro - v0;
    vec3  n = cross( v1v0, v2v0 );
    vec3  q = cross( rov0, rd );
    float d = 1.0/dot( rd, n );
    float u = d*dot( -q, v2v0 );
    float v = d*dot(  q, v1v0 );
    float t = d*dot( -n, rov0 );
    if( u<0.0 || v<0.0 || (u+v)>1.0 ) t = -1.0;
    return vec3( t, u, v );
}

vec2 sphIntersect( in vec3 ro, in vec3 rd, float ra )
{
    float b = dot( ro, rd );
    float c = dot( ro, ro ) - ra*ra;
    float h = b*b - c;
    if( h<0.0 ) return vec2(-1.0); // no intersection
    h = sqrt( h );
    return vec2( -b-h, -b+h );
}

vec2 boxIntersection( in vec3 ro, in vec3 rd, in vec3 rad, out vec3 oN ) 
{
    vec3 m = 1.0/rd; // can precompute if traversing a set of aligned boxes
    vec3 n = m*ro;   // can precompute if traversing a set of aligned boxes
    vec3 k = abs(m)*rad;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
    float tN = max( max( t1.x, t1.y ), t1.z );
    float tF = min( min( t2.x, t2.y ), t2.z );
    if( tN>tF || tF<0.0) return vec2(-1.0); // no intersection
    oN = -sign(rd) * step(t1.yzx,t1.xyz) * step(t1.zxy,t1.xyz);
    return vec2( tN, tF );
}

float plaIntersect( in vec3 ro, in vec3 rd, in vec4 p )
{
    return -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
}

vec3 castRay(inout vec3 ro, inout vec3 rd)
{
	vec3 col;
	vec2 minIt = vec2(MAX_DIST);
	vec2 it;
	vec3 n;
	vec3 spherePos = vec3(0.0, -1.0, 0.0);
	it = sphIntersect(ro - spherePos,rd,1.0);
	if(it.x > 0.0 && it.x < minIt.x)
	{
		minIt = it;
		vec3 itPos = ro + rd * it.x;
		n = itPos - spherePos;
		col = vec3(1.0,0.2,0.1);
	}
	vec3 boxN;
	vec3 boxPos = vec3(0.0, 2.0, 0.0);
	it = boxIntersection(ro - boxPos, rd, vec3(1.0), boxN);
	if(it.x > 0.0 && it.x < minIt.x)
	{
		minIt = it;
		n = boxN;
		col = vec3(0.4,0.6,0.8);
	}
	vec3 planeNormal = vec3(0.0, 0.0, -1.0);
	it = plaIntersect(ro, rd, vec4(planeNormal, 1.0));
	if(it.x > 0.0 && it.x < minIt.x)
	{
		minIt = it;
		n = planeNormal;
		col = vec3(0.5);
	}
	vec3 v0 = vec3(-1.0, -1.0, -2.0);
	vec3 v1 = vec3(-1.0, 1.0, -2.0);
	vec3 v2 = vec3(-1.0, 0.5, -4.0);
	it = triIntersect(ro,rd,v0,v1,v2);
	if(it.x > 0.0 && it.x < minIt.x)
	{
		minIt = it;
		n = (0.0, -1.0, 0.0);
		col = (0.6, 0.2, 0.4);
	}
	if(minIt.x == MAX_DIST) return vec3(-1.0);
	float diffuse = dot(light,n) * 0.5 + 0.5;
	float specular = max(0.0, pow(dot(reflect(rd,n),light),32.0) * 2.0);
	col *= mix(diffuse, specular,0.5);
	ro += rd * (minIt.x - 0.001);
	rd = n;
	return col;
}
vec3 traceRay(vec3 ro, vec3 rd)
{
	vec3 col = castRay(ro,rd);
	if(col.x == -1.0) return getSky(rd);
	vec3 lightDir = light;
	if(dot(rd, light) > 0)
	{
		if(castRay(ro, lightDir).x != -1.0) col *= 0.5;
	}
	return col;
}

void main()
{
	vec2 uv = (gl_TexCoord[0].xy-0.5) * u_resolution / u_resolution.y;
	vec3 rayOrigin = u_pos;
	vec3 rayDirection = normalize(vec3(1.0,uv));
	rayDirection.zx *= rot(-u_mouse.y);
	rayDirection.xy *= rot(u_mouse.x);
	vec3 col = traceRay(rayOrigin,rayDirection);
	col.r = pow(col.r, 0.45);
	col.g = pow(col.g, 0.45);
	col.b = pow(col.b, 0.45);
	gl_FragColor = vec4(col, 1.0);
}