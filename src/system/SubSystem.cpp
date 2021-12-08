/*
 * MIT License
 *
 * Alexandria.org
 *
 * Copyright (c) 2021 Josef Cullhed, <info@alexandria.org>, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "SubSystem.h"
#include "Logger.h"

SubSystem::SubSystem() {

	init_aws_api();

	setenv("AWS_EC2_METADATA_DISABLED", "true", 1);
	auto credentialsProvider = Aws::MakeShared<Aws::Auth::EnvironmentAWSCredentialsProvider>("asd");
	m_s3_client = new Aws::S3::S3Client(credentialsProvider, get_s3_config());
	m_lambda_client = new Aws::Lambda::LambdaClient(credentialsProvider, get_s3_config());

	LOG_INFO("download domain_info.tsv");
	TsvFileRemote domain_index(System::domain_index_filename());
	m_domain_index = new Dictionary(domain_index);

	LOG_INFO("download dictionary.tsv");
	TsvFileRemote dictionary(System::dictionary_filename());
	m_dictionary = new Dictionary(dictionary);

	dictionary.read_column_into(0, m_words);

	sort(m_words.begin(), m_words.end(), [](const string &a, const string &b) {
		return a < b;
	});
}

SubSystem::~SubSystem() {
	delete m_dictionary;
	delete m_domain_index;
	delete m_s3_client;
	delete m_lambda_client;

	//deinit_aws_api();
}

const Dictionary *SubSystem::domain_index() const {
	return m_domain_index;
}

const Dictionary *SubSystem::dictionary() const {
	return m_dictionary;
}

const vector<string> SubSystem::words() const {
	return m_words;
}

const Aws::S3::S3Client SubSystem::s3_client() const {
	return *m_s3_client;
}

const Aws::Lambda::LambdaClient SubSystem::lambda_client() const {
	return *m_lambda_client;
}

void SubSystem::init_aws_api() {
	LOG_INFO("init aws api");
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Off;
	options.loggingOptions.logger_create_fn = get_logger_factory();

	Aws::InitAPI(options);
}

void SubSystem::deinit_aws_api() {
	Aws::SDKOptions options;
	Aws::ShutdownAPI(options);
}

Aws::Client::ClientConfiguration SubSystem::get_s3_config() {

	Aws::Client::ClientConfiguration config;
	config.region = "us-east-1";
	config.scheme = Aws::Http::Scheme::HTTP;
	config.verifySSL = false;
	config.requestTimeoutMs = 300000; // 5 minutes
	config.connectTimeoutMs = 300000; // 5 minutes

	return config;
}

