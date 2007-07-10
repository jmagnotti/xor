package sshbuddy;

import java.io.File;
import java.io.IOException;

import com.sshtools.j2ssh.authentication.PasswordAuthenticationClient;
import com.sshtools.j2ssh.authentication.PublicKeyAuthenticationClient;
import com.sshtools.j2ssh.authentication.SshAuthenticationClient;
import com.sshtools.j2ssh.transport.publickey.SshPrivateKeyFile;

public class WallManager
{
	private SshAuthenticationClient authClient;
	private String					baseHostname;
	private int loRange, hiRange;
	
	
	/**
	 * Using this constructor will connect to nodes using 
	 * a username and password.
	 * 
	 * @param username
	 * @param password
	 */
	public WallManager(String baseHostname, String username, String password,
			int loRange, int hiRange, boolean pass)
	{
		this.baseHostname = baseHostname;
		setRange(loRange, hiRange);
		// pwc lets us authenticate later with a password
		PasswordAuthenticationClient pwc = new PasswordAuthenticationClient();
		pwc.setUsername(username);
		pwc.setPassword(password);
		
		// now "cast" it to our more abstract type so we can hand it off later
		authClient = pwc;
	}
	
	/**
	 * This constructor will connect to nodes using a public key. 
	 * 
	 * @param pathToKey path to the key file (can be absolute or relative)
	 */
	public WallManager (String hostname, String username, String pathToKey,
			int loRange, int hiRange) throws IOException
	{
		this.baseHostname = hostname;
		setRange(loRange, hiRange);
		// load the private key file, should have no keyword protection
		SshPrivateKeyFile file =
			SshPrivateKeyFile.parse(new File(pathToKey));
	    PublicKeyAuthenticationClient pk = new PublicKeyAuthenticationClient();
	    pk.setUsername(username);
	    pk.setKey(file.toPrivateKey(null));
	    
	    authClient = pk;
	}
	
	/**
	 * Validates and sets the range of host names
	 * @param loRange Lower end of the range
	 * @param hiRange Higher end of the range
	 */
	public void setRange(int loRange, int hiRange)
	{
		if(loRange <= hiRange && loRange >= 0) {
			this.loRange = loRange;
			this.hiRange = hiRange;
		} else {
			System.out.println("Incorrect range!");
		}
	}
	
	
}
