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

#include "Api.h"
#include "ApiResponse.h"

#include "post_processor/PostProcessor.h"

#include "full_text/SearchMetric.h"

#include "search_engine/SearchEngine.h"
#include "stats/Stats.h"

#include "LinkResult.h"
#include "DomainLinkResult.h"

#include "system/Logger.h"
#include "system/Profiler.h"

namespace Api {

	void search(const string &query, HashTable &hash_table, vector<FullTextIndex<FullTextRecord> *> index_array,
		vector<FullTextIndex<LinkFullTextRecord> *> link_index_array, vector<FullTextIndex<DomainLinkFullTextRecord> *> domain_link_index_array,
		stringstream &response_stream) {

		Profiler::instance profiler;

		struct SearchMetric metric;
		SearchEngine::reset_search_metric(metric);

		Profiler::instance profiler_links("SearchEngine::search<LinkFullTextRecord>");
		vector<LinkFullTextRecord> links = SearchEngine::search<LinkFullTextRecord>(link_index_array, {}, {}, query, 500000, metric);
		profiler_links.stop();

		sort(links.begin(), links.end(), [](const LinkFullTextRecord &a, const LinkFullTextRecord &b) {
			return a.m_target_hash < b.m_target_hash;
		});

		metric.m_links_handled = links.size();
		metric.m_total_url_links_found = metric.m_total_found;

		metric.m_total_found = 0;

		vector<DomainLinkFullTextRecord> domain_links;
		if (domain_link_index_array.size()) {
			Profiler::instance profiler_domain_links("SearchEngine::search<DomainLinkFullTextRecord>");
			domain_links = SearchEngine::search<DomainLinkFullTextRecord>(domain_link_index_array, {}, {}, query, 10000, metric);
			profiler_domain_links.stop();

			metric.m_total_domain_links_found = metric.m_total_found;
		}

		Profiler::instance profiler_index("SearchEngine::search_with_links");
		vector<FullTextRecord> results = SearchEngine::search_deduplicate(index_array, links, domain_links, query, 1000, metric);
		profiler_index.stop();

		PostProcessor post_processor(query);

		vector<ResultWithSnippet> with_snippets;
		for (FullTextRecord &res : results) {
			const string tsv_data = hash_table.find(res.m_value);
			with_snippets.emplace_back(ResultWithSnippet(tsv_data, res));
		}

		post_processor.run(with_snippets);

		ApiResponse response(with_snippets, metric, profiler.get());

		response_stream << response;
	}

	void search_all(const string &query, HashTable &hash_table, vector<FullTextIndex<FullTextRecord> *> index_array,
		vector<FullTextIndex<LinkFullTextRecord> *> link_index_array, vector<FullTextIndex<DomainLinkFullTextRecord> *> domain_link_index_array,
		stringstream &response_stream) {

		Profiler::instance profiler;

		struct SearchMetric metric;
		SearchEngine::reset_search_metric(metric);

		Profiler::instance profiler_links("SearchEngine::search<LinkFullTextRecord>");
		vector<LinkFullTextRecord> links = SearchEngine::search<LinkFullTextRecord>(link_index_array, {}, {}, query, 500000, metric);
		profiler_links.stop();

		sort(links.begin(), links.end(), [](const LinkFullTextRecord &a, const LinkFullTextRecord &b) {
			return a.m_target_hash < b.m_target_hash;
		});

		metric.m_total_url_links_found = metric.m_total_found;

		metric.m_total_found = 0;

		Profiler::instance profiler_domain_links("SearchEngine::search<DomainLinkFullTextRecord>");
		vector<DomainLinkFullTextRecord> domain_links = SearchEngine::search<DomainLinkFullTextRecord>(domain_link_index_array, {}, {}, query, 10000,
			metric);
		profiler_domain_links.stop();

		metric.m_total_domain_links_found = metric.m_total_found;

		Profiler::instance profiler_index("SearchEngine::search_with_links");
		vector<FullTextRecord> results = SearchEngine::search(index_array, links, domain_links, query, 1000, metric);
		profiler_index.stop();

		PostProcessor post_processor(query);

		vector<ResultWithSnippet> with_snippets;
		for (FullTextRecord &res : results) {
			const string tsv_data = hash_table.find(res.m_value);
			with_snippets.emplace_back(ResultWithSnippet(tsv_data, res));
		}

		post_processor.run(with_snippets);

		ApiResponse response(with_snippets, metric, profiler.get());

		response_stream << response;
	}

	Aws::Utils::Json::JsonValue generate_word_stats_json(const map<string, double> word_map) {
		Aws::Utils::Json::JsonValue result;
		for (const auto &iter : word_map) {
			Aws::Utils::Json::JsonValue json_number;
			result.WithObject(iter.first, json_number.AsDouble(iter.second));
		}

		return result;
	}

	Aws::Utils::Json::JsonValue generate_index_stats_json(const map<string, double> word_map, size_t index_size) {
		Aws::Utils::Json::JsonValue result, total;
		result.WithObject("total", total.AsInt64(index_size));
		result.WithObject("words", generate_word_stats_json(word_map));
		return result;
	}

	void word_stats(const string &query, vector<FullTextIndex<FullTextRecord> *> index_array,
		vector<FullTextIndex<LinkFullTextRecord> *> link_index_array, size_t index_size, size_t link_index_size, stringstream &response_stream) {

		Profiler::instance profiler;

		map<string, double> word_stats = Stats::word_stats<FullTextRecord>(index_array, query, index_size);
		map<string, double> link_word_stats = Stats::word_stats<LinkFullTextRecord>(link_index_array, query, link_index_size);

		double time_ms = profiler.get();

		Aws::Utils::Json::JsonValue message("{}"), json_string;
		message.WithObject("status", json_string.AsString("success"));
		message.WithObject("time_ms", json_string.AsDouble(time_ms));
		message.WithObject("index", generate_index_stats_json(word_stats, index_size));
		message.WithObject("link_index", generate_index_stats_json(link_word_stats, link_index_size));

		response_stream << message.View().WriteReadable();
	}

	void url(const string &url_str, HashTable &hash_table, stringstream &response_stream) {
		Profiler::instance profiler;

		URL url(url_str);

		Aws::Utils::Json::JsonValue message("{}"), json_string;
		message.WithObject("status", json_string.AsString("success"));
		message.WithObject("response", json_string.AsString(hash_table.find(url.hash())));
		message.WithObject("time_ms", json_string.AsDouble(profiler.get()));

		response_stream << message.View().WriteReadable();
	}

}

