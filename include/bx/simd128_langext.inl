/*
 * Copyright 2010-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef BX_SIMD_LANGEXT_H_HEADER_GUARD
#define BX_SIMD_LANGEXT_H_HEADER_GUARD

#define float4_rcp           float4_rcp_ni
#define float4_orx           float4_orx_ni
#define float4_orc           float4_orc_ni
#define float4_neg           float4_neg_ni
#define float4_madd          float4_madd_ni
#define float4_nmsub         float4_nmsub_ni
#define float4_div_nr        float4_div_nr_ni
#define float4_selb          float4_selb_ni
#define float4_sels          float4_sels_ni
#define float4_not           float4_not_ni
#define float4_abs           float4_abs_ni
#define float4_clamp         float4_clamp_ni
#define float4_lerp          float4_lerp_ni
#define float4_rcp_est       float4_rcp_ni
#define float4_rsqrt         float4_rsqrt_ni
#define float4_rsqrt_nr      float4_rsqrt_nr_ni
#define float4_rsqrt_carmack float4_rsqrt_carmack_ni
#define float4_sqrt_nr       float4_sqrt_nr_ni
#define float4_log2          float4_log2_ni
#define float4_exp2          float4_exp2_ni
#define float4_pow           float4_pow_ni
#define float4_cross3        float4_cross3_ni
#define float4_normalize3    float4_normalize3_ni
#define float4_dot3          float4_dot3_ni
#define float4_dot           float4_dot_ni
#define float4_ceil          float4_ceil_ni
#define float4_floor         float4_floor_ni
#define float4_min           float4_min_ni
#define float4_max           float4_max_ni
#define float4_imin          float4_imin_ni
#define float4_imax          float4_imax_ni

#include "simd_ni.inl"

namespace bx
{
#define ELEMx 0
#define ELEMy 1
#define ELEMz 2
#define ELEMw 3
#define BX_SIMD128_IMPLEMENT_SWIZZLE(_x, _y, _z, _w) \
			template<> \
			BX_SIMD_FORCE_INLINE simd_langext_t float4_swiz_##_x##_y##_z##_w(simd_langext_t _a) \
			{ \
				simd_langext_t result; \
				result.vf = __builtin_shufflevector(_a.vf, _a.vf, ELEM##_x, ELEM##_y, ELEM##_z, ELEM##_w); \
				return result; \
			}

#include "float4_swizzle.inl"

#undef BX_SIMD128_IMPLEMENT_SWIZZLE
#undef ELEMw
#undef ELEMz
#undef ELEMy
#undef ELEMx

#define BX_SIMD128_IMPLEMENT_TEST(_xyzw, _mask) \
			template<> \
			BX_SIMD_FORCE_INLINE bool simd_test_any_##_xyzw(simd_langext_t _test) \
			{ \
				uint32_t tmp = ( (_test.uxyzw[3]>>31)<<3) \
				             | ( (_test.uxyzw[2]>>31)<<2) \
				             | ( (_test.uxyzw[1]>>31)<<1) \
				             | (  _test.uxyzw[0]>>31)     \
				             ; \
				return 0 != (tmp&(_mask) ); \
			} \
			\
			template<> \
			BX_SIMD_FORCE_INLINE bool simd_test_all_##_xyzw(simd_langext_t _test) \
			{ \
				uint32_t tmp = ( (_test.uxyzw[3]>>31)<<3) \
				             | ( (_test.uxyzw[2]>>31)<<2) \
				             | ( (_test.uxyzw[1]>>31)<<1) \
				             | (  _test.uxyzw[0]>>31)     \
				             ; \
				return (_mask) == (tmp&(_mask) ); \
			}

BX_SIMD128_IMPLEMENT_TEST(x    , 0x1);
BX_SIMD128_IMPLEMENT_TEST(y    , 0x2);
BX_SIMD128_IMPLEMENT_TEST(xy   , 0x3);
BX_SIMD128_IMPLEMENT_TEST(z    , 0x4);
BX_SIMD128_IMPLEMENT_TEST(xz   , 0x5);
BX_SIMD128_IMPLEMENT_TEST(yz   , 0x6);
BX_SIMD128_IMPLEMENT_TEST(xyz  , 0x7);
BX_SIMD128_IMPLEMENT_TEST(w    , 0x8);
BX_SIMD128_IMPLEMENT_TEST(xw   , 0x9);
BX_SIMD128_IMPLEMENT_TEST(yw   , 0xa);
BX_SIMD128_IMPLEMENT_TEST(xyw  , 0xb);
BX_SIMD128_IMPLEMENT_TEST(zw   , 0xc);
BX_SIMD128_IMPLEMENT_TEST(xzw  , 0xd);
BX_SIMD128_IMPLEMENT_TEST(yzw  , 0xe);
BX_SIMD128_IMPLEMENT_TEST(xyzw , 0xf);

#undef BX_SIMD128_IMPLEMENT_TEST

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_xyAB(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 0, 1, 4, 5);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_ABxy(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 4, 5, 0, 1);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_CDzw(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 6, 7, 2, 3);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_zwCD(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 2, 3, 6, 7);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_xAyB(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 0, 4, 1, 5);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_yBxA(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 1, 5, 0, 4);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_zCwD(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 2, 6, 3, 7);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_CzDw(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 6, 2, 7, 3);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_xAzC(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 0, 4, 2, 6);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_shuf_yBwD(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = __builtin_shufflevector(_a.vf, _b.vf, 1, 5, 3, 7);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE float float4_x(simd_langext_t _a)
	{
		return _a.fxyzw[0];
	}

	template<>
	BX_SIMD_FORCE_INLINE float float4_y(simd_langext_t _a)
	{
		return _a.fxyzw[1];
	}

	template<>
	BX_SIMD_FORCE_INLINE float float4_z(simd_langext_t _a)
	{
		return _a.fxyzw[2];
	}

	template<>
	BX_SIMD_FORCE_INLINE float float4_w(simd_langext_t _a)
	{
		return _a.fxyzw[3];
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_ld(const void* _ptr)
	{
		const uint32_t* input = reinterpret_cast<const uint32_t*>(_ptr);
		simd_langext_t result;
		result.uxyzw[0] = input[0];
		result.uxyzw[1] = input[1];
		result.uxyzw[2] = input[2];
		result.uxyzw[3] = input[3];
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE void float4_st(void* _ptr, simd_langext_t _a)
	{
		uint32_t* result = reinterpret_cast<uint32_t*>(_ptr);
		result[0] = _a.uxyzw[0];
		result[1] = _a.uxyzw[1];
		result[2] = _a.uxyzw[2];
		result[3] = _a.uxyzw[3];
	}

	template<>
	BX_SIMD_FORCE_INLINE void float4_stx(void* _ptr, simd_langext_t _a)
	{
		uint32_t* result = reinterpret_cast<uint32_t*>(_ptr);
		result[0] = _a.uxyzw[0];
	}

	template<>
	BX_SIMD_FORCE_INLINE void float4_stream(void* _ptr, simd_langext_t _a)
	{
		uint32_t* result = reinterpret_cast<uint32_t*>(_ptr);
		result[0] = _a.uxyzw[0];
		result[1] = _a.uxyzw[1];
		result[2] = _a.uxyzw[2];
		result[3] = _a.uxyzw[3];
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_ld(float _x, float _y, float _z, float _w)
	{
		simd_langext_t result;
		result.vf = (float __attribute__((vector_size(16)))){ _x, _y, _z, _w };
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_ild(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w)
	{
		simd_langext_t result;
		result.vu = (uint32_t __attribute__((vector_size(16)))){ _x, _y, _z, _w };
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_splat(const void* _ptr)
	{
		const uint32_t val = *reinterpret_cast<const uint32_t*>(_ptr);
		simd_langext_t result;
		result.vu = (uint32_t __attribute__((vector_size(16)))){ val, val, val, val };
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_splat(float _a)
	{
		return float4_ld<simd_langext_t>(_a, _a, _a, _a);
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_isplat(uint32_t _a)
	{
		return float4_ild<simd_langext_t>(_a, _a, _a, _a);
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_zero()
	{
		return float4_ild<simd_langext_t>(0, 0, 0, 0);
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_itof(simd_langext_t _a)
	{
		simd_langext_t result;
		result.vf = __builtin_convertvector(_a.vi, float __attribute__((vector_size(16))) );
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_ftoi(simd_langext_t _a)
	{
		simd_langext_t result;
		result.vi = __builtin_convertvector(_a.vf, int32_t __attribute__((vector_size(16))) );
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_round(simd_langext_t _a)
	{
		const simd_langext_t tmp    = float4_ftoi(_a);
		const simd_langext_t result = float4_itof(tmp);

		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_add(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = _a.vf + _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_sub(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = _a.vf - _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_mul(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = _a.vf * _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_div(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vf = _a.vf / _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_sqrt(simd_langext_t _a)
	{
		simd_langext_t result;
		result.vf[0] = sqrtf(_a.vf[0]);
		result.vf[1] = sqrtf(_a.vf[1]);
		result.vf[2] = sqrtf(_a.vf[2]);
		result.vf[3] = sqrtf(_a.vf[3]);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_rsqrt_est(simd_langext_t _a)
	{
		simd_langext_t result;
		result.vf[0] = 1.0f / sqrtf(_a.vf[0]);
		result.vf[1] = 1.0f / sqrtf(_a.vf[1]);
		result.vf[2] = 1.0f / sqrtf(_a.vf[2]);
		result.vf[3] = 1.0f / sqrtf(_a.vf[3]);
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_cmpeq(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vf == _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_cmplt(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vf < _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_cmple(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vf <= _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_cmpgt(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vf > _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_cmpge(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vf >= _b.vf;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_and(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vu = _a.vu & _b.vu;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_andc(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vu = _a.vu & ~_b.vu;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_or(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vu = _a.vu | _b.vu;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_xor(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vu = _a.vu ^ _b.vu;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_sll(simd_langext_t _a, int _count)
	{
		simd_langext_t result;
		const simd_langext_t count = float4_isplat<simd_langext_t>(_count);
		result.vu = _a.vu << count.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_srl(simd_langext_t _a, int _count)
	{
		simd_langext_t result;
		const simd_langext_t count = float4_isplat<simd_langext_t>(_count);
		result.vu = _a.vu >> count.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_sra(simd_langext_t _a, int _count)
	{
		simd_langext_t result;
		const simd_langext_t count = float4_isplat<simd_langext_t>(_count);
		result.vi = _a.vi >> count.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_icmpeq(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vi == _b.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_icmplt(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vi < _b.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_icmpgt(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vi > _b.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_iadd(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vi + _b.vi;
		return result;
	}

	template<>
	BX_SIMD_FORCE_INLINE simd_langext_t float4_isub(simd_langext_t _a, simd_langext_t _b)
	{
		simd_langext_t result;
		result.vi = _a.vi - _b.vi;
		return result;
	}

	typedef simd_langext_t simd128_t;

} // namespace bx

#endif // BX_SIMD_LANGEXT_H_HEADER_GUARD