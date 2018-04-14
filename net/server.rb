require 'em-websocket'
require 'json'


# {
# "movement": {
#   "team": 0,
#   "player_id": 1,
#   "x_diff": -1,
#   "y_diff": 1
# }
# }
#

#
# broadcast all ruby related tweets to all connected users!
#
EM.run {
  team_0 = true
  curr_id = 1
  @channel = EM::Channel.new

  EM::WebSocket.start(:host => "127.0.0.1", :port => 8080) do |ws|

    ws.onopen {
      team = team_0 ? 0 : 1
      team_0 = !team_0 && true
      ws.send('{"id":' + curr_id.to_s + ', "team":' + team.to_s + '}')
      sid  = @channel.subscribe { |msg|
        ws.send(msg)
      }

      x_pos = 123
      y_pos = 321
      @channel.push('{"register":
        {
          "player_id":' + curr_id.to_s +
          ', "team":' + team.to_s +
          ', "X":' + x_pos.to_s +
          ', "Y":' + y_pos.to_s +
      '}}')
      ws.onmessage { |msg|
        @channel.push msg
      }

      ws.onclose {
        @channel.unsubscribe(sid  )
      }
      curr_id += 1
    }

  end

  puts "Server started"
}
