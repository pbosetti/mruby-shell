n = ARGV[0].to_i or 1


n.times do |i|
  async "sleep #{rand(8)}"
end

while $&.size > 0 do
  p $&
  sleep 0.5
end

puts "done!"