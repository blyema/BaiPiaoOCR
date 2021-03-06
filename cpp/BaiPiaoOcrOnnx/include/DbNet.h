#ifndef __OCR_DBNET_H__
#define __OCR_DBNET_H__

#include "OcrStruct.h"
#include "onnxruntime_cxx_api.h"
#include <opencv/cv.hpp>

class DbNet {
public:
    DbNet();

    ~DbNet();

    void setNumThread(int numOfThread);

    void initModel(const std::string &pathStr);

    std::vector<TextBox> getTextBoxes(cv::Mat &src, ScaleParam &s, float boxScoreThresh,
                                      float boxThresh, float unClipRatio);

private:
    Ort::Session *session;
    Ort::Env env = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "DbNet");
    Ort::SessionOptions sessionOptions = Ort::SessionOptions();
    int numThread = 0;
    std::vector<char *> inputNames;
    std::vector<char *> outputNames;

    const float meanValues[3] = {0.485f * 255, 0.456f * 255, 0.406f * 255};
    const float normValues[3] = {1.0 / 0.229f / 255.0, 1.0 / 0.224f / 255.0, 1.0 / 0.225f / 255.0};
};


#endif //__OCR_DBNET_H__
