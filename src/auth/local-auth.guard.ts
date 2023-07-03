import { ExecutionContext, Injectable } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

// Authentiseringsstrategi for Passport (bruker LocalStrategy)
@Injectable()
export class LocalAuthGuard extends AuthGuard('local') {
  async canActivate(context: ExecutionContext) {
    const result = (await super.canActivate(context)) as boolean;
    const req = context.switchToHttp().getRequest();

    await super.logIn(req);
    return result;
  }
}
