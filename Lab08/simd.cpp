#include <iostream>
#include <cstdlib>
#include <chrono>
#include <immintrin.h>
#include <omp.h>
using std::cout;
using std::endl;

#define TIME_START start=std::chrono::steady_clock::now();
#define TIME_END(NAME) end=std::chrono::steady_clock::now(); \
             duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\
             cout<<(NAME)<<": result="<<result \
             <<", duration = "<<duration<<"ms"<<endl;

float avx2_add(float * p1, float * p2, size_t size) {
    float sum[8] = {0.0f};
    
    __m256 a, b, c = _mm256_setzero_ps();
    for (int i = 0; i < size; i += 8) {
        a = _mm256_load_ps(p1 + i);
        b = _mm256_load_ps(p2 + i);
        c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    _mm256_store_ps(sum, c);
    return (sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]);
}

float avx2_omp_add(float * p1, float * p2, size_t size) {
    float sum[8] = {0.0f};
    
    __m256 a, b, c = _mm256_setzero_ps();
    #pragma omp parallel for
    for (int i = 0; i < size; i += 8) {
        a = _mm256_load_ps(p1 + i);
        b = _mm256_load_ps(p2 + i);
        c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    _mm256_store_ps(sum, c);
    return (sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]);
}

int main() {

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto duration = 0L;

    size_t nSize = 200000000;

    float * p1 = static_cast<float*>(aligned_alloc(256, nSize*sizeof(float))); 
    float * p2 = static_cast<float*>(aligned_alloc(256, nSize*sizeof(float)));
    float result = 0.0f;

    p1[1] = 1.f;
    p2[1] = 2.f;
    p1[nSize - 1] = 3.f;
    p2[nSize - 1] = 4.f;

    TIME_START;
    result = avx2_add(p1, p2, nSize);
    TIME_END("AVX2_ADD");

    TIME_START;
    result = avx2_omp_add(p1, p2, nSize);
    TIME_END("AVX2_ADD_OMP");

}