import sys




def split_h_file(aFilename):
    if aFilename.endswith('.h'):
        f = open(aFilename, 'r')
        lines = f.readlines()
        f.close();
        
        lineNr = 0
        while lineNr < len(lines):
            line = lines[lineNr]
            if(line.startswith('class')):
                words = line.split()
                name = words[1].split(':')[0]
                if(not name.endswith(';')):
                    name = name.rstrip('{')
                    
                    cap_name = name.upper()
                    low_name = name.lower()
                    nf = open(low_name+'.h', 'wb')
                    nf.write('#ifndef _H_'+cap_name+'\n')
                    nf.write('#define _H_'+cap_name+'\n\n')
                    
                    while not line.startswith('}'):
                        nf.write(line)
                        lineNr += 1
                        line = lines[lineNr]
                    
                    lineNr -= 1
                    nf.write(line)
                    nf.write('\n#endif // _H_'+cap_name+'\n\n\n')
                    nf.close()
                    
            lineNr += 1
    else:
        print 'ERROR: onyl for header files!!'
    
def split_cpp_file(aFilename):
    if aFilename.endswith('.cpp'):
        f = open(aFilename, 'r')
        lines = f.readlines()
        f.close()
        
        data = {} # {fname: [lines]}
        
        lineNr = 0
        while lineNr < len(lines):
            line = lines[lineNr]
            tline = line.strip()
            words = line.split()
            if 2 <= len(words):
                word = words[1]
            elif 1 == len(words):
                word = words[0]
            else:
                word = ''
            names = word.split('::')
            if 2 == len(names) and tline.endswith("{"):
                print 
                filelines = data.get(names[0].lower(), [])
                if not len(filelines):
                    filelines.append('#include "actions/'+names[0].lower()+'.h"\n\n\n')
                    filelines.append('//'+'-'*58 + '//\n')
                while not line[0]=='}' and lineNr < len(lines):
                    line = lines[lineNr]
                    filelines.append(line)
                    lineNr += 1
                lineNr -= 1
                filelines.append('//'+'-'*58 + '//\n')
                data[names[0].lower()] = filelines
            lineNr += 1
            
        for key, val in data.items():
            print key
            f = open(key+'.cpp', 'wb')
            for line in val:
                f.write(line)
            f.write('\n')   
            f.close()
            
    else:
        print 'ERROR: only for *.cpp files'
    
if __name__=='__main__':
    fname = sys.argv[1]
    if fname.endswith('.h'):
        split_h_file(fname)
    if fname.endswith('.cpp'):
        split_cpp_file(fname)