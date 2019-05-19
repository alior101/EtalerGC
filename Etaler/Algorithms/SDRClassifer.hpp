#pragma once

#include <Etaler/Core/Tensor.hpp>

#include <vector>

namespace et
{

struct SDRClassifer
{
	SDRClassifer() = default;
	SDRClassifer(Shape input_shape, size_t num_classes)
		: input_shape_(input_shape), references_(num_classes, zeros(input_shape))
		, num_patterns_(num_classes)
	{
	}

	void addPattern(const Tensor& sdr, size_t class_id)
	{
		et_assert(sdr.shape() == input_shape_);
		et_assert(sdr.dtype() == DType::Bool);
		et_assert(class_id < references_.size());

		references_[class_id] = references_[class_id] + sdr;
	}

	size_t compute(const Tensor& x, float min_common_frac=0.75) const
	{
		size_t best_match_id = -1;
		size_t best_match = 0;
		for(size_t i=0;i<references_.size();i++) {
			int threshold = num_patterns_[i]*min_common_frac;
			size_t overlaps = sum((references_[i] > threshold) && x).toHost<int32_t>()[0];

			if(overlaps > best_match)
				std::tie(best_match_id, best_match) = std::pair(i, overlaps);
		}
		return best_match;
	}

	Shape input_shape_;
	std::vector<Tensor> references_;
	std::vector<uint32_t> num_patterns_;
};

}