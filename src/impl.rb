#puts 'Using Orientation';
puts 'Enter the class name: '
name = gets().gsub("\n",""); #"Orientation"
	
header_file = name + ".h"
cpp_file = name + ".cpp"

#puts "try with: " + header_file
_h = IO.readlines(header_file)
_cpp = IO.readlines(cpp_file)

_h_methods = []
_cpp_methods = []

_h.each do |line| 
	if line.include?("/**")
		wait_for_end = true
	elsif wait_for_end && line.include?("*/")
		wait_for_end = false
	end

	unless  wait_for_end
		_h_methods <<  line.gsub("\t","").gsub(";","") if line.include?("(") && line.include?(";") && ! line.include?("//")
	end
end

_cpp.each { |line|
	_cpp_methods << line.gsub(name + "::", "") if line.include?(name + "::")
}

_h_methods.each { |n|
	puts("Need to implement " + n.to_s) unless _cpp_methods.include?(n)
}

