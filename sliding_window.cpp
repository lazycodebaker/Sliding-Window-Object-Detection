#include "vector"
#include "iostream"
#include "chrono"
#include "thread"
#include "opencv2/dnn.hpp"
#include "opencv2/opencv.hpp"

// Constants for file paths and window size
const std::string IMAGE_PATH = "/Users/lazycodebaker/Desktop/How-to-Use-Sliding-Windows-for-Object-Detection-in-OpenCV-and-Python/1.jpg";
const std::string PROTOTXT_PATH = "/Users/lazycodebaker/Desktop/How-to-Use-Sliding-Windows-for-Object-Detection-in-OpenCV-and-Python/MobileNetSSD_deploy.prototxt.txt";
const std::string CAFFEMODEL_PATH = "/Users/lazycodebaker/Desktop/How-to-Use-Sliding-Windows-for-Object-Detection-in-OpenCV-and-Python/MobileNetSSD_deploy.caffemodel";
const size_t W_SIZE = 128; // Window size for sliding window

// List of object classes that the MobileNet SSD model can detect
const std::vector<std::string> classes = {
    "background", "aeroplane", "bicycle", "bird", "boat",
    "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
    "dog", "horse", "motorbike", "person", "pottedplant",
    "sheep", "sofa", "train", "tvmonitor"};

// Lambda function for implementing a sliding window over an image
auto slidingWindow = [](const cv::Mat &image, int stepSize, const cv::Size &windowSize) -> std::vector<cv::Rect>
{
    std::vector<cv::Rect> windows;
    // Loop through the image with the specified step size
    for (int y = 0; y <= image.rows - windowSize.height; y += stepSize)
    {
        for (int x = 0; x <= image.cols - windowSize.width; x += stepSize)
        {
            // Add the current window (rectangle) to the list
            windows.emplace_back(x, y, windowSize.width, windowSize.height);
        }
    }
    return windows;
};

// Function to visualize sliding windows and perform object detection
void visualizeSlidingWindow(const cv::Mat &image, cv::dnn::Net &net, const std::vector<std::string> &classes, int stepSize, const cv::Size &windowSize, cv::Mat &outputImage)
{
    // Generate a list of sliding window rectangles
    std::vector<cv::Rect> windows = slidingWindow(image, stepSize, windowSize);

    for (const auto &rect : windows)
    {
        // Extract the sub-image corresponding to the current window
        cv::Mat window = image(rect);

        // Skip if the window size is incorrect (e.g., at edges of the image)
        if (window.size() != windowSize)
            continue;

        // Preprocess the window for input to the neural network
        cv::Mat blob = cv::dnn::blobFromImage(window, 0.007843, windowSize, 127.5);
        net.setInput(blob);

        // Perform forward pass to get detections
        cv::Mat detections = net.forward();

        // Process detections for the current window
        for (int i = 0; i < detections.size[2]; ++i)
        {
            float confidence = static_cast<float>(detections.ptr<float>(0)[i * 7 + 2]);

            // Only consider detections with confidence above 0.6
            if (confidence > 0.6)
            {
                int idx = static_cast<int>(detections.ptr<float>(0)[i * 7 + 1]);
                std::string label = classes[idx];

                // Draw a red rectangle and label for the detected object
                cv::rectangle(outputImage, rect, cv::Scalar(0, 0, 255), 2);
                cv::putText(outputImage, label, cv::Point(rect.x, rect.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
            }
        }

        // Visualize the sliding window with a green rectangle
        cv::Mat clone = image.clone();
        cv::rectangle(clone, rect, cv::Scalar(0, 255, 0), 2);

        // Display the sliding window in a window titled "Sliding Window"
        cv::imshow("Sliding Window", clone);

        // Exit visualization on 'Esc' key press
        if (cv::waitKey(25) == 27)
            break;

        // Add a delay to slow down the sliding window visualization
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}

int main()
{
    // Load the pre-trained MobileNet SSD model
    cv::dnn::Net net = cv::dnn::readNetFromCaffe(PROTOTXT_PATH, CAFFEMODEL_PATH);

    // Read the input image
    cv::Mat image = cv::imread(IMAGE_PATH);

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cerr << "Error: Image not found at the specified path." << std::endl;
        return -1;
    }

    // Define step size and window size for sliding window
    int stepSize = 32;
    cv::Size windowSize = cv::Size(W_SIZE, W_SIZE);

    // Clone the input image for drawing detections
    cv::Mat outputImage = image.clone();

    // Perform sliding window visualization and object detection
    visualizeSlidingWindow(image, net, classes, stepSize, windowSize, outputImage);

    // Display the final image with detected objects
    cv::imshow("Detected Objects", outputImage);
    cv::waitKey(0); // Wait for a key press before exiting
    cv::destroyAllWindows();

    // Save the output image with detections
    cv::imwrite("output_with_detections.jpg", outputImage);

    return EXIT_SUCCESS;
}