import { Injectable } from '@nestjs/common';
import { UserService } from 'src/user/user.service';

@Injectable()
export class AuthService {
  constructor(private usersService: UserService) {}

  async validateUser(username: string, passsword: string): Promise<any> {
    const user = await this.usersService.findOneByUsername(username);

    if (user && user.password === passsword) {
      const { password, username, ...rest } = user;
      return rest;
    }
    return null;
  }
}
