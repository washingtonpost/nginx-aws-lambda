#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/ratelimiter/DefaultRateLimiter.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/lambda/LambdaClient.h>
#include <aws/lambda/model/InvokeRequest.h>
#include <aws/core/utils/Outcome.h>

using namespace Aws::Lambda;
using namespace Aws::Lambda::Model;

int main() {
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    Aws::InitAPI(options);

    //use the sdk
    const char* ALLOCATION_TAG = "nginx_aws_lambda";
    auto m_limiter = Aws::MakeShared<Aws::Utils::RateLimits::DefaultRateLimiter<>>(ALLOCATION_TAG, 200000);

    // Create a client
    Aws::Client::ClientConfiguration config;
    config.scheme = Aws::Http::Scheme::HTTPS;
    config.connectTimeoutMs = 30000;
    config.requestTimeoutMs = 30000;
    config.readRateLimiter = m_limiter;
    config.writeRateLimiter = m_limiter;

    //to test proxy functionality, uncomment the next two lines.
    std::shared_ptr<LambdaClient> lambdaClient = Aws::MakeShared<LambdaClient>(ALLOCATION_TAG, config);
    InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName("test");
    invokeRequest.SetInvocationType(InvocationType::RequestResponse);

    InvokeOutcome invokeOutcome = lambdaClient->Invoke(invokeRequest);
    if (invokeOutcome.IsSuccess()) {
        auto &result = invokeOutcome.GetResult();
        std::cout << "Status" + std::to_string(result.GetStatusCode()) << std::endl;
    } else {
        auto &error = invokeOutcome.GetError();
        std::cout << "Error" + error.GetMessage() << std::endl;
    }

    Aws::ShutdownAPI(options);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}