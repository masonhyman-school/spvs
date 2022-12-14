#ifndef SPVS_HEADER_FILE_H
#define SPVS_HEADER_FILE_H

/* Supports service fingerprinting for ports */
class Services
{
	public:
		Services (const std::string&);
		Services (const std::string&, std::vector<int>&);
		std::string Get_Port_Name(int);
	private:
		std::map<int, std::string> service_map;
};

/* Defines information for single target. */
class Target
{
	public:
		Target (std::string&);

		bool ICMP_Host_Online(const std::string&);
		void TCP_Port_Is_Open(const std::string&, const int);
		void TCP_Scan_Ports(const std::string&, const std::vector<int>&);		
	
	/* Accessor / Information Functions */
		void TCP_Print_Open_Ports();
		const std::string& Get_Address();
		void Set_Online(bool);

		void Print_Target(Services *);
	private:
		bool online;
		std::string address;
		std::vector<int> open_ports; 
};

/* Input Parser */
class Input
{
	public:
		Input (int &argc, char ** argv);

		bool Arg_Exists(const std::string &option) const;
		const std::string& Get_Next_Arg(const std::string & option) const;

		std::vector<Target *> Get_Targets_From_File(const std::string&);
		std::vector<Target *> Get_Targets_From_Stdin();
		std::vector<int> Get_Ports_To_Scan(const std::string&);
	private:
		std::list<std::string> args;
};


/* Overarching SPVS Class. Drives program */
class SPVS
{
	public:
		SPVS (int &argc, char ** argv);
		void Scan_Targets();

		void Print_Usage();
		void Print_Targets();
		void Print_Ports();
	private:
		Input * input;
		Services * services;
		std::vector<Target *> targets;
		std::vector<int> ports_to_scan;
};

#endif
