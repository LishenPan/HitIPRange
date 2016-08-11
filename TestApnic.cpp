// TestApnic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")

struct ip_range
{
	unsigned int ip_begin_;
	unsigned int ip_end_;
	ip_range(unsigned int begin, unsigned int end)
		: ip_begin_(begin), ip_end_(end){}
	ip_range()
		: ip_begin_(0), ip_end_(0){}
	bool operator < (const ip_range& other) const 
	{
		if (ip_begin_ < other.ip_begin_)
			return true;
		else
			return false;
	}
};

bool prepare_ip_table(std::vector<ip_range>& container, const std::string& file);
unsigned int query_self_isp(const std::vector<ip_range>& container, const std::string& addr);

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<ip_range> vec_chinanet_ip_table_;
	std::vector<ip_range> vec_unicom_ip_table_;
	std::vector<ip_range> vec_gwbn_ip_table_;
	std::vector<ip_range> vec_cernet_ip_table_;
	std::vector<ip_range> vec_chinabtn_ip_table_;
	std::vector<ip_range> vec_cstnet_ip_table_;
	std::vector<ip_range> vec_cttnet_ip_table_;
	std::vector<ip_range> vec_cmcc_ip_table_;
	std::vector<ip_range> vec_colnet_ip_table_;
	std::vector<ip_range> vec_topwaynet_ip_table_;
	std::vector<ip_range> vec_etrunk_ip_table_;
	std::vector<ip_range> vec_founderbn_ip_table_;

	std::string findip("110.77.96.45");

	do {
		bool ret = prepare_ip_table(vec_chinanet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/chinanet");
		if (ret) {
			int netType = query_self_isp(vec_chinanet_ip_table_, findip);
			if (netType) {
				std::cout << "chinanet" << std::endl;
				break;
			}
		}
	
		ret = prepare_ip_table(vec_unicom_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/unicom");
		if (ret) {
			int netType = query_self_isp(vec_unicom_ip_table_, findip);
			if (netType) {
				std::cout << "unicom" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_gwbn_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/gwbn");
		if (ret) {
			int netType = query_self_isp(vec_gwbn_ip_table_, findip);
			if (netType) {
				std::cout << "gwbn" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_cernet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/cernet");
		if (ret) {
			int netType = query_self_isp(vec_cernet_ip_table_, findip);
			if (netType) {
				std::cout << "cernet" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_chinabtn_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/chinabtn");
		if (ret) {
			int netType = query_self_isp(vec_chinabtn_ip_table_, findip);
			if (netType) {
				std::cout << "chinabtn" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_cstnet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/cstnet");
		if (ret) {
			int netType = query_self_isp(vec_cstnet_ip_table_, findip);
			if (netType) {
				std::cout << "cstnet" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_cttnet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/cttnet");
		if (ret) {
			int netType = query_self_isp(vec_cttnet_ip_table_, findip);
			if (netType) {
				std::cout << "cttnet" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_cmcc_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/cmcc");
		if (ret) {
			int netType = query_self_isp(vec_cmcc_ip_table_, findip);
			if (netType) {
				std::cout << "cmcc" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_colnet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/colnet");
		if (ret) {
			int netType = query_self_isp(vec_colnet_ip_table_, findip);
			if (netType) {
				std::cout << "colnet" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_topwaynet_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/topwaynet");
		if (ret) {
			int netType = query_self_isp(vec_topwaynet_ip_table_, findip);
			if (netType) {
				std::cout << "topwaynet" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_etrunk_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/etrunk");
		if (ret) {
			int netType = query_self_isp(vec_etrunk_ip_table_, findip);
			if (netType) {
				std::cout << "etrunk" << std::endl;
				break;
			}
		}

		ret = prepare_ip_table(vec_founderbn_ip_table_, "I:/MyWorks/iSpeak/_server/src/TestApnic/founderbn");
		if (ret) {
			int netType = query_self_isp(vec_founderbn_ip_table_, findip);
			if (netType) {
				std::cout << "founderbn" << std::endl;
				break;
			}
		}
	} while(0);

	return 0;
}

bool prepare_ip_table(std::vector<ip_range>& container, const std::string& file)
{
  // 文本格式: IP/MaskBit
	char buf[32]={0};
  FILE* fpIn = fopen(file.c_str(), "r");
  if(fpIn == NULL)
    return false;
	unsigned int line=0;

  while(!feof(fpIn))
  {
    fgets(buf, 32, fpIn);
    char* ch = buf;

		if (*ch == '#') 
			continue;

    do 
    {
      if (*(++ch) == '/')
        break;
    } while (ch < &buf[31]);

    *ch = '\0';
    unsigned int ip = inet_addr(buf);
    if(ip == 0xFFFFFFFF)
      continue;

    ip = ntohl(ip);
    unsigned int bit = atoi(ch + 1);
    if(bit > 24 || bit < 1)
      continue;

    unsigned int mask = 0xFFFFFFFF << (32 - bit);

    unsigned int ip_Begin = (ip & mask) + 0x00000001;
    unsigned int ip_End = ip_Begin + (0xFFFFFFFF - mask) - 0x0000001;

		//for (unsigned int i = ip_Begin; i <= ip_End; i++) {
			//in_addr tt;
			//tt.S_un.S_addr = htonl(ip_Begin);
			//std::cout << "begin: " << ip_Begin << " --- " << inet_ntoa(tt) << std::endl;
			//tt.S_un.S_addr = htonl(ip_End);
			//std::cout << "end: " << ip_End << " --- " << inet_ntoa(tt) << std::endl;
		//}

		line++;
    ip_range range(ip_Begin, ip_End);
    container.push_back(range);
  }

	std::cout << file << " : " << line << std::endl;

  fclose(fpIn);
  fpIn = 0;   

  std::sort(container.begin(), container.end());

  return true;
}

unsigned int query_self_isp(const std::vector<ip_range>& container, const std::string& addr) 
{
	unsigned int size = 0;
	unsigned int ip = inet_addr(addr.c_str());
	ip = ntohl(ip);

	size = container.size();
	if (size) {
		unsigned int mid = 0;
		unsigned int left = 0;
		unsigned int right = size - 1;
		while (left <= right) {
			mid = left + (right - left) / 2;
			if (mid > size - 1) break;

			unsigned int begin = container[mid].ip_begin_;
			unsigned int end = container[mid].ip_end_;
			if (ip > begin && ip > end)
				left = mid + 1;
			else if (ip < end && ip < begin)
				right = mid - 1;
			else {
				in_addr tt;
				tt.S_un.S_addr = htonl(begin);
				std::cout << "begin: " << begin << " --- " << inet_ntoa(tt) << std::endl;
				tt.S_un.S_addr = htonl(end);
				std::cout << "end: " << end << " --- " << inet_ntoa(tt) << std::endl;
				tt.S_un.S_addr = htonl(ip);
				std::cout << "ip: " << ip << " --- " << inet_ntoa(tt) << std::endl;
				return 1;
			}
		}
	}

  return 0;
}
