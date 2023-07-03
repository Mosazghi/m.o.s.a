import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-local';
import { AuthService } from './auth.service';

// Authentiseringsstrategi for Passport (bruker LocalStrategy)
@Injectable()
export class LocalStrategy extends PassportStrategy(Strategy) {
  constructor(private authService: AuthService) {
    super();
  }

  async validate(username: string, passsword: string): Promise<any> {
    const user = await this.authService.validateUser(username, passsword);

    if (!user) {
      throw new UnauthorizedException();
    }
    return user;
  }
}
