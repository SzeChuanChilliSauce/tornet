#ifndef _TORNET_UDT_CHANNEL_HPP_
#define _TORNET_UDT_CHANNEL_HPP_
#include <tornet/net/channel.hpp>
#include <boost/asio.hpp>

namespace tornet {

  /**
   *  Provides in-order, gauranteed delivery of streams of
   *  data using a protocol similar to UDT.  All processing is
   *  done in the node thread.  Calls to write/read are posted
   *  to the node thread to complete. 
   */
  class udt_channel {
    public:
      udt_channel( const channel& c, uint16_t max_window_packets = 256 );
      ~udt_channel();

      void close();

      /**
       *  Blocks until all of @param b has been sent
       *
       *  Throws on error.
       *
       *  @return bytes read
       */
      size_t write( const boost::asio::const_buffer& b );
      
      /**
       *  Blocks until all of @param b has been filled.
       *
       *  Throws on error.
       *
       *  @return bytes read
       */
      size_t read( const boost::asio::mutable_buffer& b );
      inline size_t read( char* d, uint32_t s ) { return read( boost::asio::mutable_buffer(d,s) ); }
      inline bool   get( char& c )              { return read( boost::asio::mutable_buffer(&c,sizeof(c))); }
      inline bool   get( unsigned char& c )     { return read( boost::asio::mutable_buffer(&c,sizeof(c))); }

      scrypt::sha1 remote_node()const;
      uint8_t      remote_rank()const;

    private:
      boost::shared_ptr<class udt_channel_private> my;
  };

}

#endif
