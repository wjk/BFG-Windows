using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace sha1sum
{
    class Program
    {
        static void Main(string[] args)
        {
            var hasher = SHA1.Create();
            foreach (string filename in args)
            {
                try
                {
                    byte[] fileHash = null;
                    using (Stream stream = File.OpenRead(filename))
                    {
                        fileHash = hasher.ComputeHash(stream);
                    }

                    StringBuilder builder = new StringBuilder();
                    foreach (byte b in fileHash) builder.Append(b.ToString("x2"));
                    Console.WriteLine($"{builder.ToString()} {filename}");
                }
                catch (FileNotFoundException)
                {
                    Console.Error.WriteLine($"{filename}: File not found. Ignoring");
                }
                catch (IOException)
                {
                    Console.Error.WriteLine($"{filename}: IOException. Ignoring this file.");
                }
                catch (Exception ex)
                {
                    Console.Error.WriteLine($"{filename}: {ex.GetType().Name} was thrown. Ignoring this file.");
                }
            }
        }
    }
}
