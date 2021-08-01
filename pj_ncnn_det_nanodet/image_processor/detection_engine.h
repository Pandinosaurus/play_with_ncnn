#ifndef DETECTION_ENGINE_
#define DETECTION_ENGINE_

/* for general */
#include <cstdint>
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <memory>

/* for OpenCV */
#include <opencv2/opencv.hpp>

/* for My modules */
#include "inference_helper.h"


class DetectionEngine {
public:
	enum {
		kRetOk = 0,
		kRetErr = -1,
	};

	typedef struct {
		int32_t     class_id;
		std::string label;
		float       score;
		float       x;
		float       y;
		float       width;
		float       height;
	} Object;

	typedef struct Result_ {
		std::vector<Object> object_list;
		double              time_pre_process;	// [msec]
		double              time_inference;		// [msec]
		double              time_post_process;	// [msec]
		Result_() : time_pre_process(0), time_inference(0), time_post_process(0)
		{}
	} Result;

public:
	DetectionEngine() {}
	~DetectionEngine() {}
	int32_t Initialize(const std::string& work_dir, const int32_t num_threads);
	int32_t Finalize(void);
	int32_t Process(const cv::Mat& original_mat, Result& result);

private:
	int32_t ReadLabel(const std::string& filename, std::vector<std::string>& label_list);
	int32_t DecodeInfer(std::vector<Object>& object_list, const OutputTensorInfo& cls_pred, const OutputTensorInfo& dis_pred, double threshold, int32_t stride, int32_t model_width, int32_t model_height);
	void DisPred2Bbox(Object& object, const OutputTensorInfo& dis_pred, int32_t idx, int32_t x, int32_t y, int32_t stride);
	void Nms(std::vector<Object>& object_list, std::vector<Object>& object_list_nms, bool use_weight);
	float CalculateIoU(const Object& det0, const Object& det1);

private:
	std::unique_ptr<InferenceHelper> inference_helper_;
	std::vector<InputTensorInfo> input_tensor_info_list_;
	std::vector<OutputTensorInfo> output_tensor_info_list_;
	std::vector<std::string> label_list_;
};

#endif
