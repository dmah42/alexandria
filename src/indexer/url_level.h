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

#include "level.h"
#include "index_builder.h"

#include <unordered_map>

namespace indexer {

	class url_record : public generic_record {

		public:

		url_record() : generic_record() {};
		url_record(uint64_t value) : generic_record(value) {};
		url_record(uint64_t value, float score) : generic_record(value, score) {};

	};

	class url_level: public level {
		private:
		std::unordered_map<uint64_t, std::unique_ptr<index_builder<url_record>>> m_builders;
		std::unordered_map<uint64_t, std::unique_ptr<index_builder<link_record>>> m_link_builders;

		public:
		url_level();
		level_type get_type() const;
		void add_snippet(const snippet &s);
		void add_document(size_t id, const std::string &doc);
		void add_index_file(const std::string &local_path,
			std::function<void(uint64_t, const std::string &)> add_data,
			std::function<void(uint64_t, uint64_t)> add_url);
		void add_link_file(const std::string &local_path, const ::algorithm::bloom_filter &url_filter);
		void merge();
		void calculate_scores() {};
		void clean_up();
		std::vector<return_record> find(const std::string &query, const std::vector<size_t> &keys,
			const std::vector<link_record> &links, const std::vector<domain_link_record> &domain_links, const std::vector<counted_record> &scores, const std::vector<domain_record> &domain_modifiers);
		size_t apply_url_links(const std::vector<link_record> &links, std::vector<return_record> &results);

		private:
			index_builder<url_record> *make_sure_builder_is_present(uint64_t);
			index_builder<link_record> *make_sure_link_builder_is_present(uint64_t domain_hash);
	};

}
