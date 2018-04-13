require 'em-websocket'
require 'json'

next_team = 0
curr_id = 1

#
# broadcast all ruby related tweets to all connected users!
#
EM.run {
  @channel = EM::Channel.new

  EM::WebSocket.start(:host => "127.0.0.1", :port => 8080) do |ws|

    ws.onopen {
      team = (curr_id % 2 == 0) ? 1 : 0
      x_pos = 123
      y_pos = 321
      @channel.push('{"register":
        {
          "player_id":' + curr_id.to_s +
          ', "team":' + team.to_s +
          ', "X":' + x_pos.to_s +
          ', "Y":' + y_pos.to_s +
      '}}')

      sid  = @channel.subscribe { |msg|
        ws.send(msg)
      }

      ws.onmessage { |msg|
        @channel.push "<#{sid }>: #{msg}"
      }

      ws.onclose {
        @channel.unsubscribe(sid  )
      }
      curr_id += 1
    }

  end

  puts "Server started"
}
