#version 430 core

out vec4 result_frag_color;
in vec3 o_vertex_color;
in vec2 o_vertex_uv;


uniform vec2 mouse_pos;
uniform float time;

/******************************************************************************************/
/*
void diffuse(int b, float[] x, float[] x0, float diff, float dt) {
  float a = dt * diff * (Nx - 2) * (Ny - 2);
  lin_solve(b, x, x0, a, 1 + 6 * a);
}

void lin_solve(int b, float[] x, float[] x0, float a, float c) {
  float cRecip = 1.0 / c;
  for (int k = 0; k < iter; k++) {
    for (int j = 1; j < Ny - 1; j++) {
      for (int i = 1; i < Nx - 1; i++) {
        x[IX(i, j)] =
          (x0[IX(i, j)]
          + a*(    x[IX(i+1, j)]
          +x[IX(i-1, j)]
          +x[IX(i, j+1)]
          +x[IX(i, j-1)]
          )) * cRecip;
      }
    }
    //set_bnd(b, x);
  }
}

void project(float[] velocX, float[] velocY, float[] p, float[] div) {
  for (int j = 1; j < Ny - 1; j++) {
    for (int i = 1; i < Nx - 1; i++) {
      div[IX(i, j)] = -0.5f*(
        (velocX[IX(i+1, j)]-velocX[IX(i-1, j)])/Nx + 
        (velocY[IX(i, j+1)]-velocY[IX(i, j-1)])/Ny
        );
      p[IX(i, j)] = 0;
    }
  }
  set_bnd(0, div); 
  set_bnd(0, p);
  lin_solve(0, p, div, 1, 6);

  for (int j = 1; j < Ny - 1; j++) {
    for (int i = 1; i < Nx - 1; i++) {
      velocX[IX(i, j)] -= 0.5f * (  p[IX(i+1, j)]
        -p[IX(i-1, j)]) * Nx;
      velocY[IX(i, j)] -= 0.5f * (  p[IX(i, j+1)]
        -p[IX(i, j-1)]) * Ny;
    }
  }
  set_bnd(1, velocX);
  set_bnd(2, velocY);
}


void advect(int b, float[] d, float[] d0, float[] velocX, float[] velocY, float dt)
{
  float i0, i1, j0, j1;

  float dtx = dt * (Nx - 2);
  float dty = dt * (Ny - 2);

  float s0, s1, t0, t1;
  float tmp1, tmp2, x, y;

  float Nxfloat = Nx;
  float Nyfloat = Ny;
  float ifloat, jfloat;
  int i, j;

  for (j = 1, jfloat = 1; j < Ny - 1; j++, jfloat++) { 
    for (i = 1, ifloat = 1; i < Nx - 1; i++, ifloat++) {
      tmp1 = dtx * velocX[IX(i, j)];
      tmp2 = dty * velocY[IX(i, j)];
      x    = ifloat - tmp1; 
      y    = jfloat - tmp2;

      if (x < 0.5f) x = 0.5f; 
      if (x > Nxfloat + 0.5f) x = Nxfloat + 0.5f; 
      i0 = floor(x); 
      i1 = i0 + 1.0f;
      if (y < 0.5f) y = 0.5f; 
      if (y > Nyfloat + 0.5f) y = Nyfloat + 0.5f; 
      j0 = floor(y);
      j1 = j0 + 1.0f; 

      s1 = x - i0; 
      s0 = 1.0f - s1; 
      t1 = y - j0; 
      t0 = 1.0f - t1;

      int i0i = int(i0);
      int i1i = int(i1);
      int j0i = int(j0);
      int j1i = int(j1);

      d[IX(i, j)] = s0 * ( t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)])
        + s1 * ( t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
    }
  }

  //set_bnd(b, d);
}


void set_bnd(int b, out float x) {

  for (int i = 1; i < Nx - 1; i++) {
    x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
    x[IX(i, Ny-1)] = b == 2 ? -x[IX(i, Ny-2)] : x[IX(i, Ny-2)];
  }

  for (int j = 1; j < Ny - 1; j++) {
    x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
    x[IX(Nx-1, j)] = b == 1 ? -x[IX(Nx-2, j)] : x[IX(Nx-2, j)];
  }

  x[IX(0, 0)] = 0.5f * (x[IX(1, 0)] + x[IX(0, 1)]);
  x[IX(0, Ny-1)] = 0.5f * (x[IX(1, Ny-1)] + x[IX(0, Ny-2)]);
  x[IX(Nx-1, 0)] = 0.5f * (x[IX(Nx-2, 0)] + x[IX(Nx-1, 1)]);
  x[IX(Nx-1, Ny-1)] = 0.5f * (x[IX(Nx-2, Ny-1)] + x[IX(Nx-1, Ny-2)]);
}
*/
/******************************************************************************************/

void main()
{
    // TODO: handle them via screen size uniform...
    vec2 mouse = vec2(mouse_pos.x/1920, mouse_pos.y/1080);
    vec2 uv = o_vertex_uv;

    if (uv.x - 0.01 < mouse.x && uv.x + 0.01 > mouse.x
        &&
        uv.y - 0.01 < 1 - mouse.y && uv.y + 0.01 > 1 - mouse.y)
        result_frag_color = vec4(1.0, 1.0, 0.9, 1.0);
    else
        result_frag_color = vec4(0, 0, 0, 1);
};
