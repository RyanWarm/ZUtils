#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <stdlib.h>
#include <signal.h>
#include "Server.hpp"
namespace po = boost::program_options;


Server * g_server;

void signal_handler(int signum);
int main(int argc, char* argv[])
{
    try
    {
        short port=0;
        string index_dir="";
        string server_type="";
        string mongodb_addr="";
        string company_list_filename="";
        string company_score_filename="";
        
        po::options_description server_options("Options");
        server_options.add_options()
            ("port",  po::value<short>(&port), "server port (1024 - 65535)")
            ("index-dir", po::value<string>(&index_dir), "index dir")
            ("server-type", po::value<string>(&server_type), "server_type: user or job")
            ("mongodb-addr", po::value<string>(&mongodb_addr), "mongodb addr")
            ("contacts-company-file", po::value<string>(&company_list_filename), "company name file")
            ("company-score-file", po::value<string>(&company_score_filename), "company score file");

        po::variables_map vm; 
        store(po::command_line_parser(argc, argv).options(server_options).run(), vm);
        notify(vm);

        if(port<1025 || index_dir=="" || server_type==""){
            server_options.print(std::cerr);
            return -1;
        }
        Server::server_type_t st;
        if(server_type == "user"){
            st = Server::SERVER_TYPE_USER;
        }else if(server_type == "job"){
            st = Server::SERVER_TYPE_JOB;
        }else{
            server_options.print(std::cerr);
            return -1;
        }

        boost::asio::io_service io_service;
        g_server = new Server(io_service, port,index_dir.c_str(),st,mongodb_addr,company_list_filename,company_score_filename);
        if(false == g_server->init()){
            TB_INFO("Server init failed");
            return -1;
        }
        TB_INFO("Server init ok");
        g_server->run();
    }
    catch (const char *&e){
        TB_INFO("Exception: " << e);
    }
    catch (std::exception& e)
    {
        TB_INFO("Exception: " << e.what());
    }
    return 0;
}

