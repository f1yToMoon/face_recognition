#include <algorithm>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/imgcodecs.hpp"
#include <random>;

template<typename T>
T random(T range_to) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<T> distr(1, range_to);
    return distr(generator);
}

int main() {
    std::vector<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(random(10304));
    }

    std::vector<std::vector<int>> f, ff, fff;
    for (int i = 0; i < 40; ++i) {
        std::vector<int> hist(256);
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        mat.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
        for(int j : img) {
            hist[j]++;
        }
        f.push_back(hist);
    }

    for (int i = 0; i < 40; ++i) {
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        mat.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);

        std::vector<int> v;
        for (int j = 0; j < 1000; ++j) {
            v.push_back(img[vec[j]]);
        }

        ff.push_back(v);
    }

    int down_width = 46;
    int down_height = 56;
    for (int i = 0; i < 40; ++i) {
        cv::Mat resized_down;
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        resize(mat, resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);
        resized_down.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
        fff.push_back(img);
    }

    int k = 0;
    for (int h = 0; h < 40; ++h) {
        std::cout << h << ") ";
        float l = 0;
        for (int u = 2; u < 11; ++u) {
            std::vector<int> xRand, xHist, xResize;
            std::vector<int> testRand, testHist(256);
            cv::Mat resized_down;
            cv::Mat mat = cv::imread(
                    "/home/nick/images/archive/s" + std::to_string(h) + "/" + std::to_string(u) + ".pgm",
                    cv::IMREAD_GRAYSCALE);
            mat.convertTo(mat, CV_32F);
            std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
            resize(mat, resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);
            resized_down.convertTo(mat, CV_32F);
            std::vector<int> testResize((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);

            for (int j = 0; j < 1000; ++j) {
                testRand.push_back(img[vec[j]]);
            }

            for(int i : img) {
                testHist[i]++;
            }

            for (int i = 0; i < 40; ++i) {
                int diff1 = 0;
                for (int j = 0; j < testHist.size(); ++j) {
                    diff1 += abs(f[i][j] - testHist[j]);
                }
                xHist.push_back(diff1);
            }
            for (int i = 0; i < 40; ++i) {
                int diff2 = 0;
                for (int j = 0; j < testRand.size(); ++j) {
                    diff2 += abs(ff[i][j] - testRand[j]);
                }
                xRand.push_back(diff2);
            }
            for (int i = 0; i < 40; ++i) {
                int diff3 = 0;
                for (int j = 0; j < testResize.size(); ++j) {
                    diff3 += abs(fff[i][j] - testResize[j]);
                }
                xResize.push_back(diff3);
            }

            auto minRand = *std::min_element(xRand.begin(), xRand.end());
            auto minResize = *std::min_element(xResize.begin(), xResize.end());
            auto minHist = *std::min_element(xHist.begin(), xHist.end());
           int qr = 0, qre = 0, qh = 0;
            for (int i = 0; i < 40; ++i) {
                if (xRand[i] == minRand && h == i) {
                    qr = 1;
                }
            }
            for (int i = 0; i < 40; ++i) {
                if (xResize[i] == minResize && h == i) {
                    qre = 1;
                }
            }
            for (int i = 0; i < 40; ++i) {
                if (xHist[i] == minHist && h == i) {
                    qh = 1;
                }
            }
            if (qr == 1 || qre == 1 || qh == 1) {
                l += 1;
            }

        }
        std::cout << l << "\n";
        k += l;
    }
    std::cout << k << "/360";
    return 0;
}
