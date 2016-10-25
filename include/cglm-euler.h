/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_euler_h
#define cglm_euler_h

#include "cglm-common.h"

/*!
 * @brief euler angles (in radian) using xyz sequence
 *
 * @param[in]  m     affine transform
 * @param[out] pitch x
 * @param[out] yaw   y
 * @param[out] roll  z
 */
CGLM_INLINE
void
glm_euler_angles(mat4 m,
                 float * __restrict pitch,
                 float * __restrict yaw,
                 float * __restrict roll) {
  if (m[2][0] < 1.0f) {
    if (m[2][0] > -1.0f) {
      vec3 a[2];
      float cy1, cy2;
      int   path;

      a[0][1] = asinf(m[2][0]);
      a[1][1] = M_PI - a[0][1];

      cy1 = cosf(a[0][1]);
      cy2 = cosf(a[1][1]);

      a[0][0] = atan2f(-m[2][1] / cy1, m[2][2] / cy1);
      a[1][0] = atan2f(-m[2][1] / cy2, m[2][2] / cy2);

      a[0][2] = atan2f(-m[1][0] / cy1, m[0][0] / cy1);
      a[1][2] = atan2f(-m[1][0] / cy2, m[0][0] / cy2);

      path = (fabsf(a[0][0]) + fabsf(a[0][1]) + fabsf(a[0][2])) >
                (fabsf(a[1][0]) + fabsf(a[1][1]) + fabsf(a[1][2]));

      *pitch = a[path][0];
      *yaw   = a[path][1];
      *roll  = a[path][2];
    } else {
      *pitch = -atan2(m[0][1], m[2][1]);
      *yaw   = -M_PI_2;
      *roll  = 0.0f;
    }
  } else {
    *pitch = atan2f(m[0][1], m[1][1]);
    *yaw   = M_PI_2;
    *roll  = 0.0f;
  }
}

/*!
 * @brief euler angles (in radian) using xyz sequence
 *
 * @param[in]  m affine transform
 * @param[out] v angles vector [x, y, z]
 */
CGLM_INLINE
void
glm_euler_anglesv(mat4 m, vec3 v) {
  if (m[2][0] < 1.0f) {
    if (m[2][0] > -1.0f) {
      vec3  a[2];
      float cy1, cy2;
      int   path;

      a[0][1] = asinf(m[2][0]);
      a[1][1] = M_PI - a[0][1];

      cy1 = cosf(a[0][1]);
      cy2 = cosf(a[1][1]);

      a[0][0] = atan2f(-m[2][1] / cy1, m[2][2] / cy1);
      a[1][0] = atan2f(-m[2][1] / cy2, m[2][2] / cy2);

      a[0][2] = atan2f(-m[1][0] / cy1, m[0][0] / cy1);
      a[1][2] = atan2f(-m[1][0] / cy2, m[0][0] / cy2);

      path = (fabsf(a[0][0]) + fabsf(a[0][1]) + fabsf(a[0][2])) >
               (fabsf(a[1][0]) + fabsf(a[1][1]) + fabsf(a[1][2]));

      glm_vec_dup(a[path], v);
    } else {
      v[0] = -atan2(m[0][1], m[2][1]);
      v[1] = -M_PI_2;
      v[3] = 0.0f;
    }
  } else {
    v[0] = atan2f(m[0][1], m[1][1]);
    v[1] = M_PI_2;
    v[2] = 0;
  }
}

/*!
 * @brief build rotation matrix from euler angles(xyz)
 */
CGLM_INLINE
void
glm_euler(float pitch,
          float yaw,
          float roll,
          mat4 dest) {
  float cx, cy, cz,
        sx, sy, sz;

  sx = sinf(pitch); cx = cosf(pitch);
  sy = sinf(yaw);   cy = cosf(yaw);
  sz = sinf(roll);  cz = cosf(roll);

  dest[0][0] = cy * cz;
  dest[0][1] = cz * sx * sy + cx * sz;
  dest[0][2] =-cx * cz * sy + sx * sz;
  dest[1][0] =-cy * sz;
  dest[1][1] = cx * cz - sx * sy * sz;
  dest[1][2] = cz * sx + cx * sy * sz;
  dest[2][0] = sy;
  dest[2][1] =-cy * sx;
  dest[2][2] = cx * cy;
  dest[0][3] = 0.0f;
  dest[1][3] = 0.0f;
  dest[2][3] = 0.0f;
  dest[3][0] = 0.0f;
  dest[3][1] = 0.0f;
  dest[3][2] = 0.0f;
  dest[3][3] = 1.0f;
}

/*!
 * @brief build rotation matrix from euler angles(xyz)
 *
 * @param[in]  angles angles as vector [x, y, z]
 * @param[out] dest   rotation matrix
 */
CGLM_INLINE
void
glm_eulerv(vec3 angles, mat4 dest) {
  float cx, cy, cz,
        sx, sy, sz;

  sx = sinf(angles[0]); cx = cosf(angles[0]);
  sy = sinf(angles[1]); cy = cosf(angles[1]);
  sz = sinf(angles[2]); cz = cosf(angles[2]);

  dest[0][0] = cy * cz;
  dest[0][1] = cz * sx * sy + cx * sz;
  dest[0][2] =-cx * cz * sy + sx * sz;
  dest[1][0] =-cy * sz;
  dest[1][1] = cx * cz - sx * sy * sz;
  dest[1][2] = cz * sx + cx * sy * sz;
  dest[2][0] = sy;
  dest[2][1] =-cy * sx;
  dest[2][2] = cx * cy;
  dest[0][3] = 0.0f;
  dest[1][3] = 0.0f;
  dest[2][3] = 0.0f;
  dest[3][0] = 0.0f;
  dest[3][1] = 0.0f;
  dest[3][2] = 0.0f;
  dest[3][3] = 1.0f;
}

/*!
 * @brief build rotation matrix from euler angles (zyx)
 */
CGLM_INLINE
void
glm_euler_zyx(float yaw,
              float pitch,
              float roll,
              mat4 dest) {
  float cx, cy, cz,
        sx, sy, sz;

  sx = sinf(pitch); cx = cosf(pitch);
  sy = sinf(yaw);   cy = cosf(yaw);
  sz = sinf(roll);  cz = cosf(roll);

  dest[0][0] = cy * cz;
  dest[0][1] = cy * sz;
  dest[0][2] =-sy;
  dest[1][0] = cz * sx * sy - cx * sz;
  dest[1][1] = cx * cz + sx * sy * sz;
  dest[1][2] = cy * sx;
  dest[2][0] = cx * cz * sy + sx * sz;
  dest[2][1] =-cz * sx + cx * sy * sz;
  dest[2][2] = cx * cy;
  dest[0][3] = 0.0f;
  dest[1][3] = 0.0f;
  dest[2][3] = 0.0f;
  dest[3][0] = 0.0f;
  dest[3][1] = 0.0f;
  dest[3][2] = 0.0f;
  dest[3][3] = 1.0f;
}

/*!
 * @brief build rotation matrix from euler angles (zxy)
 */
CGLM_INLINE
void
glm_euler_zxy(float yaw,
              float pitch,
              float roll,
              mat4 dest) {
  float cx, cy, cz,
        sx, sy, sz;

  sx = sinf(pitch); cx = cosf(pitch);
  sy = sinf(yaw);   cy = cosf(yaw);
  sz = sinf(roll);  cz = cosf(roll);

  dest[0][0] = cy * cz - sx * sy * sz;
  dest[0][1] = cz * sx * sy + cy + sz;
  dest[0][2] =-cx * sy;
  dest[1][0] =-cx * sz;
  dest[1][1] = cx * cz;
  dest[1][2] = sx;
  dest[2][0] = cz * sy + cy * sx * sz;
  dest[2][1] =-cy * cz * sx + sy * sz;
  dest[2][2] = cx * cy;
  dest[0][3] = 0.0f;
  dest[1][3] = 0.0f;
  dest[2][3] = 0.0f;
  dest[3][0] = 0.0f;
  dest[3][1] = 0.0f;
  dest[3][2] = 0.0f;
  dest[3][3] = 1.0f;
}

#endif /* cglm_euler_h */