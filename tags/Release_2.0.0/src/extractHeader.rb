#creates a header file from a cpp file. It guesses (naively) at variable names.
#
# John Magnotti


class MethodSignature
    @comments
    @return_type
    @class_name
    @name
    @parameters

    def initialize(comments, name)
       @comments = comments.size > 0 ? comments : "\n"

       @return_type = name.split("::").first.split(" ")
       @class_name  = @return_type.last

       @return_type.delete(@class_name)
       @return_type.each{|val| val.gsub!(" ","") }

       @name = name.split("::").last.split("(").first.strip()

       @parameters = name.split("(").last.strip
       @parameters = "(" + @parameters.gsub("\n","")
    end

    # 5 return statements. oh no.
    def <=> (other)
        if (@class_name == @name) #CTOR
            if (other.name == @class_name)
                return @parameters <=> other.parameters
            else
                return -1 #CTOR always wins against non CTOR
            end
        elsif other.name == @class_name
            return 1
        end

        # on equality, try case-sensitive compare
        return name <=> other.name if name.downcase == other.name.downcase

        #default is a lower case compare
        return name.downcase <=> other.name.downcase 
    end

    def parameters
        return @parameters
    end

    def class_name
        return @class_name
    end

    def name
        return @name
    end

    def to_s(tablevel)
       tab = ""
       tablevel.times { tab += "    " }

       space = @return_type.size < 1 ? "" : " "

       return tab + @comments + tab +  @return_type.to_s() + space + @name + @parameters 
    end
end


block_comment = "/**\n *\n */\n"
t_block_comment = "\t/**\n\t *\n\t */\n"

block_level = 0;
signatures = [] 
private_vars = {} 
line = ""
comments = ""
comment_block = false

first_line = true

while line = gets();

    block_level -= 1 if line.include?("namespace") 

    if line

        if (line.length > 0) 

            block_level -= 1 if line.include?("}")
            block_level += 1 if line.include?("{") 

            if block_level == 0 

                if line.include?("::")
                    signatures << MethodSignature.new(comments, line)
                    comments = ""

                elsif line.include?("/*") 
                    comment_block = true
                    comments += line 

                elsif line.include?("*/")
                    comment_block = false
                    comments += line

                elsif comment_block
                    comments += line 

                end

            elsif line.include?("=") && line.split("=").first.include?("_")
                str = "_" + line.split("=").first.split("_").last.gsub(" ","")
                str = str.split("[").first if str.include?("[")
                private_vars[str] = str.gsub("\n","");
            end
        end
    end
end

puts "#ifndef " + signatures.first.class_name.upcase + "_H\n"
puts "#define " + signatures.first.class_name.upcase + "_H\n"
puts "\n\n"

puts "namespace XOR {\n\n"
puts "#{block_comment}class #{signatures.first.class_name}\n{\n"
puts "\npublic:\n\n"

signatures.sort.each{|sig| puts  sig.to_s(1) + ";\n\n\n" }

puts "private:\n"

private_vars.sort.each{|key,val| puts "\t" + val.to_s.gsub("_","").capitalize() + " * " + val.to_s() + ";\n"}

puts "};\n\n"
puts "}\n\n"

puts "#endif\t\t\t// #{signatures.first.class_name.upcase}_H\n\n"

