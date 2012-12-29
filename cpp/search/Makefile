EXTRAFLAGS		= -g -Wall -Werror -DMONGO_HAVE_STDINT 
CXXFLAGS        +=  -DUSER_TOPIC_STREAM_SERVER
INCLUDES		=  -I/usr/local/include

CXXFLAGS        = $(INCLUDES) $(EXTRAFLAGS) 

LIBS			= -lpthread \
				  -lboost_system \
				  -lboost_filesystem \
				  -lboost_program_options \
				  -lboost_date_time \
				  -lboost_thread \
				  -L/usr/local/lib -lxapian -lprotobuf \
				  -lmongoc \
				  -lcrypto

AR              = ar rc
CP				= cp -f 
RM				= rm -f 

OBJS			= Main.o Server.o Session.o \
				  UserSearchQuery.pb.o UserSearchResult.pb.o SearchStats.o UserDistance.o \
				  JobSearchQuery.pb.o JobSearchResult.pb.o \
				  UserSearchSession.o UserSearchWeight.o UserSearchQuery.o \
				  JobSearchSession.o JobSearchWeight.o JobSearchQuery.o \
				  CompanyContactsKeeper.o CompanyScoreKeeper.o 
T		= search_engine 

all: $(T) 

$(T): $(OBJS) 
	$(CXX)  $(CXXFLAGS) -o $@  $^ $(LIBS)

clean:
	$(RM) $(T) $(OBJS) 


