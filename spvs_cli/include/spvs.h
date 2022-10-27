#ifndef SPVS_HEADER_FILE_H
#define SPVS_HEADER_FILE_H

class Target
{
	public:
		bool ICMP_Host_Online(const std::string&);
		void TCP_Port_Is_Open(const std::string&, const int);
		void TCP_Scan_Ports(const std::string&, const std::vector<int>&);		
	
	/* Accessor / Information Functions */
		void TCP_Print_Open_Ports();
	private:
		std::vector<int> open_ports; 
};

#endif
