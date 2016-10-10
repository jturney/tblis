#include "tblis_replicate.hpp"

#include "tblis_config.hpp"

namespace tblis
{

template <typename T>
int tensor_replicate_ref(const std::vector<len_type>& len_B,
                         const std::vector<len_type>& len_AB,
                         T alpha, const T* TBLIS_RESTRICT A, const std::vector<stride_type>& stride_A_AB,
                         T  beta,       T* TBLIS_RESTRICT B, const std::vector<stride_type>& stride_B_B,
                                                             const std::vector<stride_type>& stride_B_AB)
{
    MArray::viterator<1> iter_B(len_B, stride_B_B);
    MArray::viterator<2> iter_AB(len_AB, stride_A_AB, stride_B_AB);

    while (iter_AB.next(A, B))
    {
        T temp = alpha*(*A);

        if (beta == T(0))
        {
            while (iter_B.next(B))
            {
                *B = temp;
            }
        }
        else if (beta == T(1))
        {
            while (iter_B.next(B))
            {
                *B += temp;
            }
        }
        else
        {
            while (iter_B.next(B))
            {
                *B = temp + beta*(*B);
            }
        }
    }

    return 0;
}

#define INSTANTIATE_FOR_TYPE(T) \
template \
int tensor_replicate_ref<T>(const std::vector<idx_type>& len_B, \
                            const std::vector<idx_type>& len_AB, \
                            T alpha, const T* A, const std::vector<stride_type>& stride_A_AB, \
                            T  beta,       T* B, const std::vector<stride_type>& stride_B_B, \
                                                 const std::vector<stride_type>& stride_B_AB);
#include "tblis_instantiate_for_types.hpp"

}